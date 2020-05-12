/*
 * Copyright (c) 2009-2020, Albertas Vyšniauskas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of the software author nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GPICK_COMMON_SPAN_H_
#define GPICK_COMMON_SPAN_H_
#include <iterator>
namespace common {
template<typename T, typename Size = size_t>
struct Span {
	struct Iterator {
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = Size;
		using pointer = T*;
		using reference = T&;
		Iterator(Span &span, Size position):
			m_span(span),
			m_position(position) {
		}
		bool operator!=(const Iterator &iterator) const {
			return m_span != iterator.m_span || m_position != iterator.m_position;
		}
		bool operator==(const Iterator &iterator) const {
			return m_span == iterator.m_span && m_position == iterator.m_position;
		}
		Size operator-(const Iterator &iterator) const {
			return m_position - iterator.m_position;
		}
		Iterator &operator++() {
			m_position++;
			return *this;
		}
		const T &operator*() const {
			return m_span.m_data[m_position];
		}
		T &operator*() {
			return m_span.m_data[m_position];
		}
	private:
		Span &m_span;
		Size m_position;
	};
	struct ConstIterator {
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = Size;
		using pointer = T*;
		using reference = T&;
		ConstIterator(const Span &span, Size position):
			m_span(span),
			m_position(position) {
		}
		bool operator!=(const ConstIterator &iterator) const {
			return m_span != iterator.m_span || m_position != iterator.m_position;
		}
		bool operator==(const ConstIterator &iterator) const {
			return m_span == iterator.m_span && m_position == iterator.m_position;
		}
		Size operator-(const ConstIterator &iterator) const {
			return m_position - iterator.m_position;
		}
		ConstIterator &operator++() {
			m_position++;
			return *this;
		}
		const T &operator*() const {
			return m_span.m_data[m_position];
		}
		T &operator*() {
			return m_span.m_data[m_position];
		}
	private:
		const Span &m_span;
		Size m_position;
	};
	Span():
		m_data(nullptr) {
	}
	Span(T *data, Size size):
		m_data(data),
		m_size(size) {
	}
	Span(T *start, T *end):
		m_data(start),
		m_size(static_cast<uintptr_t>(end - start) / sizeof(T)) {
	}
	Span(const Span &span):
		m_data(span.m_data),
		m_size(span.m_size) {
	}
	Span &operator=(const Span &span) {
		m_data = span.m_data;
		m_size = span.m_size;
		return *this;
	}
	explicit operator bool() const {
		return m_data != nullptr && m_size > 0;
	}
	bool operator==(const Span &span) const {
		return m_data == span.m_data && m_size == span.m_size;
	}
	bool operator!=(const Span &span) const {
		return m_data != span.m_data || m_size != span.m_size;
	}
	Iterator begin() {
		return Iterator(*this, 0);
	}
	Iterator end() {
		return Iterator(*this, m_size);
	}
	ConstIterator begin() const {
		return ConstIterator(*this, 0);
	}
	ConstIterator end() const {
		return ConstIterator(*this, m_size);
	}
	Size size() const {
		return m_size;
	}
private:
	T *m_data;
	Size m_size;
	friend Iterator;
	friend ConstIterator;
};
};
#endif /* GPICK_COMMON_SPAN_H_ */
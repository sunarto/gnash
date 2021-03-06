// accumulator.h: accumulating value for boost program_options.
// 
//   Copyright (C) 2010, 2011 Free Software Foundation, Inc
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef PROGRAM_OPTIONS_ACCUMULATOR_HPP
#define PROGRAM_OPTIONS_ACCUMULATOR_HPP

#include <boost/program_options/value_semantic.hpp>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <vector>
#include <string>

/// An accumulating option value to handle multiple incrementing options.
template<typename T>
class accumulator_type : public boost::program_options::value_semantic
{
public:

    accumulator_type() : _interval(1), _default(0) {}

    /// Set the notifier function.
    accumulator_type* notifier(boost::function1<void, const T&> f) {
        _notifier = f;
        return this;
    }

    /// Set the default value for this option.
    accumulator_type* default_value(const T& t) {
        _default = t;
        return this;
    }

    /// Set the implicit value for this option.
    //
    /// Unlike for program_options::value, this specifies a value
    /// to be applied on each occurence of the option.
    accumulator_type* implicit_value(const T& t) {
        _interval = t;
        return this;
    }

    virtual std::string name() const { return std::string(); }

    /// There are no tokens for an accumulator_type
    virtual unsigned min_tokens() const { return 0; }
    virtual unsigned max_tokens() const { return 0; }

    /// Accumulating from different sources is silly.
    virtual bool is_composing() const { return false; }

    /// Requiring one or more appearances is unlikely.
    virtual bool is_required() const { return false; }
    
    /// Every appearance of the option simply increments the value
    //
    /// There should never be any tokens.
    virtual void parse(boost::any& value_store, 
                       const std::vector<std::string>& new_tokens,
                       bool /*utf8*/) const
    {
        assert(new_tokens.empty());
        if (value_store.empty()) value_store = T();
        boost::any_cast<T&>(value_store) += _interval;
    }

    /// If the option doesn't appear, this is the default value.
    virtual bool apply_default(boost::any& value_store) const {
        value_store = _default;
        return true;
    }
 
    /// Notify the user function with the value of the value store.                              
    virtual void notify(const boost::any& value_store) const {
        if (_notifier) _notifier(boost::any_cast<T>(value_store));
    }
    
    virtual ~accumulator_type() {}

private:
    boost::function1<void, const T&> _notifier;
    T _interval;
    T _default;
};

template<typename T>
accumulator_type<T>* accumulator() {
    return new accumulator_type<T>();
}

#endif

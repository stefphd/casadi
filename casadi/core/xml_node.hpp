/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef CASADI_XML_NODE_HPP
#define CASADI_XML_NODE_HPP

#include <string>
#include <vector>
#include <map>
#include "exception.hpp"
#include "casadi_common.hpp"

/// \cond INTERNAL

namespace casadi {

  class CASADI_EXPORT XmlNode {
  public:
    /** \brief Constructor */
    XmlNode();

    /** \brief Destructor */
    ~XmlNode();

    /** \brief  Check if an attribute is present */
    bool has_attribute(const std::string& att_name) const;

    /** \brief  Add an attribute */
    void set_attribute(const std::string& att_name, const std::string& att);

    /** \brief  Get an attribute by its name */
    template<typename T>
    T attribute(const std::string& att_name) const {
      // Find the attribute, if any
      auto it = attributes_.find(att_name);
      casadi_assert(it != attributes_.end(), "Could not find attribute " + att_name);
      // Attribute found, read it
      T ret;
      readString(it->second, ret);
      return ret;
    }

    /** \brief  Get an attribute by its name, default value if not found */
    template<typename T>
    T attribute(const std::string& att_name, const T& def_att) const {
      // Find the attribute, if any
      auto it = attributes_.find(att_name);
      if (it == attributes_.end()) {
        // No such attribute, return default value
        return def_att;
      } else {
        // Attribute found, read it
        T ret;
        readString(it->second, ret);
        return ret;
      }
    }

    /** \brief  Get a reference to a child by its index */
    const XmlNode& operator[](casadi_int i) const;

    /** \brief  Get a reference to a child by its index */
    XmlNode& operator[](casadi_int i);

    /** \brief  Get a reference to a child by its name */
    const XmlNode& operator[](const std::string& childname) const;

    /** \brief  Get a reference to a child by its name */
    XmlNode& operator[](const std::string& childname);

    /** \brief  Check if a child is present */
    bool has_child(const std::string& childname) const;

    /** \brief  Get the number of children */
    casadi_int size() const;

    /** \brief  Get the name of the node */
    const std::string& name() const;

    /** \brief  Set the name of the node */
    void setName(const std::string& name);

    /** \brief  check if the name is equal to something */
    bool checkName(const std::string& str) const;

    /** \brief  Get the text field */
    std::string getText() const { return text_; }

    /** \brief  Get value of text field */
    template<typename T>
      void getText(T& val) const { readString(text_, val);}

    /** \brief  Read the string value of a string (i.e. copy) */
    static void readString(const std::string& str, std::string& val);

    /** \brief  Read the boolean value of a string */
    static void readString(const std::string& str, bool& val);

    /** \brief  Read the integer value of a string */
    static void readString(const std::string& str, casadi_int& val);

    /** \brief  Read the double value of a string */
    static void readString(const std::string& str, double& val);

    /** \brief  Read a vector of integer values of a string */
    static void readString(const std::string& str, std::vector<casadi_int>& val);

    CASADI_EXPORT friend std::ostream& operator<<(std::ostream &stream,
                                                       const XmlNode& node);

    void dump(std::ostream &stream, casadi_int indent=0) const;

    std::map<std::string, std::string>  attributes_;
    std::vector<XmlNode>                children_;
    std::map<std::string, casadi_int>           child_indices_; // the index of the children
    // sorted by their name

    std::string name_;
    std::string comment_;
    std::string text_;
  };

} // namespace casadi
/// \endcond

#endif // CASADI_XML_NODE_HPP
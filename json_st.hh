#ifndef JSON_ST_HH
#define JSON_ST_HH

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>
#include <memory>
#include <cassert>


namespace JSON 
{

    /** Possible JSON type of a value (array, object, bool, ...). */
    enum ValueType
    {
        INT,        // JSON's int
        FLOAT,      // JSON's float 3.14 12e-10
        BOOL,       // JSON's boolean (true, false)
        STRING,     // JSON's string " ... " or (not really JSON) ' ... '
        OBJECT,     // JSON's object { ... }
        ARRAY,      // JSON's array [ ... ]
        NIL         // JSON's null
    };

    /** A JSON value. Can have either type in ValueTypes. */
    class Value
    {
    public:

        using map_t = std::map<std::string, Value>;
        using vector_t = std::vector<Value>;

        /** Default constructor (type = NIL). */
        Value();

        ~Value();

        Value(ValueType vt) : type_t(vt) {
            switch(vt) {
                case ARRAY:
                    array_v = new vector_t;
                    break;
                case OBJECT:
                    object_v = new map_t;
                    break;
            }
        }
    
        /** Copy constructor. */
        Value(const Value& v);
    
        /** Constructor from int. */
        Value(const long i);
    
        /** Constructor from float. */
        Value(const double f);
    
        /** Constructor from bool. */
        Value(const bool b);
    
        /** Constructor from pointer to char (C-string).  */
        Value(const char* s);

        /** Constructor from STD string  */
        Value(const std::string& s);
    
        /** Move constructor. */
        Value( Value&& v);
    
        /** Move constructor from STD string  */
        Value(const std::string&& s);
    
        /** Type query. */
        ValueType type() const
        {
            return type_t;
        }
    
        /** Assignment operator. */
        Value& operator=(const Value& v);
    
        /** Move operator. */
        Value& operator=( Value&& v);
    
        /** Cast operator for float */
        operator float() const { return float_v; }

        operator double() const { return float_v; }
    
        /** Cast operator for float */
        operator int() const { return int_v; }

        operator long() const { return int_v; }
    
        /** Cast operator for float */
        operator bool() const { return bool_v; }
    
        /** Cast operator for float */
        operator std::string () const { return string_v; }
    
        // Array Access Methods -> push_back, operator[], at()
        void push_back(Value& v) {
            type_check(ARRAY);
            (*array_v).push_back(v);
        }

        void push_back(Value&& v) {
            type_check(ARRAY);
            (*array_v).push_back(std::move(v));
        }

        Value& operator[] (size_t i) {
            type_check(ARRAY);
            return (*array_v)[i];
        }

        const Value& operator[] (size_t i) const {
            type_check(ARRAY);
            return (*array_v)[i];  
        }

        Value& at(size_t i) {
            type_check(ARRAY);
            return (*array_v).at(i);
        }

        const Value& at(size_t i) const {
            type_check(ARRAY);
            return (*array_v).at(i);
        }

        // Object Methods
        // operator[], insert, emplace...
        void emplace(std::string&& k, Value&& v) {
            type_check(OBJECT);
            (*object_v).emplace(k, v);
        }

        Value& operator[] (const std::string& k) {
            type_check(OBJECT);
            return (*object_v)[k];
        }

        Value& operator[] (const char *k) {
            type_check(OBJECT);
            return (*object_v)[k];
        }

        size_t size() const {
            return type_t == ARRAY ? (*array_v).size() : (*object_v).size();
        }

        void print(std::ostream& out) const;

        void dp() const;

    private:

        void type_check(const ValueType& v) const {
            assert(("Given type and requested type are not same", type_t == v));
        }

    protected:
    


        // Actual Value
        double           float_v = 0;
        long             int_v = 0;
        bool             bool_v = false;
        std::string      string_v;
        map_t            *object_v = nullptr;
        vector_t         *array_v = nullptr;

        // Tag        
        ValueType       type_t;


    };
}

std::ostream& operator<<(std::ostream& o, const JSON::Value& v);
#endif

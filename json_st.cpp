#include "json_st.hh"

using namespace std;
namespace JSON {


Value::Value() : type_t(NIL) { }

Value::~Value() {
    switch(type_t) {
        case ARRAY:
            if(array_v) delete array_v;
            break;
        case OBJECT:
            if (object_v) delete object_v;
            break;
    }
}

Value::Value(const long i) : int_v(i), type_t(INT) { }

Value::Value(const double f) : float_v(f), type_t(FLOAT) { }

Value::Value(const bool b) : bool_v(b), type_t(BOOL) { }

Value::Value(const char* s) : string_v(s), type_t(STRING) { }

Value::Value(const string& s) : string_v(s), type_t(STRING) { }

Value::Value(const string&& s) : string_v(move(s)), type_t(STRING) { }

Value::Value(const Value& v)
{ 
//    std::cerr << "Copy" << std::endl;
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = v.string_v;
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = new vector_t(*v.array_v);
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = new map_t(*v.object_v);
            type_t = OBJECT;
            break;
        
    }
}

Value::Value( Value&& v)
{ 
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = move(v.string_v);
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = move(v.array_v);
            v.array_v = nullptr;
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = std::move(v.object_v);
            v.object_v = nullptr;
            type_t = OBJECT;
            break;
        
    }
}

Value& Value::operator=(const Value& v)
{
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = v.string_v;
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = new vector_t(*v.array_v);
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = new map_t(*v.object_v);
            type_t = OBJECT;
            break;
        
    }
    
    return *this;

}

Value& Value::operator=( Value&& v)
{
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = move(v.string_v);
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = std::move(v.array_v);
            v.array_v = nullptr;
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = std::move(v.object_v);
            v.object_v = nullptr;
            type_t = OBJECT;
            break;
        
    }
    
    return *this;

}

void Value::print(std::ostream& out) const {
    bool first = true;
    switch (type()) {
        case INT:
            out << int_v;
            break;
        case FLOAT:
            out << float_v;
            break;
        case BOOL:
            out << (bool_v ? "true" : "false");
            break;
        case NIL:
            out << "null"; break;
        case STRING:
            out << "\"" << string_v << "\""; break;
        case ARRAY:
            out << "[";
            for(const auto& e : *array_v) {
                if (!first)
                    out << ", ";
                e.print(out);
                first = false;
            }
            out << "]";
            break;
        case OBJECT:
            out << "{";
            for(const auto& e : *object_v) {
                if (!first)
                    out << ", ";
                out << "\""<< e.first <<"\" : ";
                e.second.print(out);
                first = false;
            }
            out << "}";
            break;
    }
}

void Value::dp() const {
    print(std::cout);
}

}

std::ostream& operator<<(std::ostream& o, const JSON::Value& v) {
    v.print(o);
    return o;
}

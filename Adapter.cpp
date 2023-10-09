
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


class Connection {
public:
    std::vector<std::string> execute(std::string query) {
        std::cout << "Executing query: " << query << std::endl;
        std::vector<std::string> data = {"row1", "row2", "row3"};
        return data;
    }
};

class ResultSet {
private:
    std::vector<std::string> data;
public:
    
    ResultSet(std::vector<std::string> data) {
        this->data = data;
    }

    
    std::vector<std::string> get_data() {
        return data;
    }
};


class Object {
private:
    
    std::string name;
public:
    
    Object(std::string name) {
        this->name = name;
    }

    
    std::string get_name() {
        return name;
    }

    
    bool operator==(const Object& other) const {
        return name == other.name;
    }
};


class ORM {
public:
    
    Object query(std::string sql) {
        
        
        Connection conn;
        ResultSet rs = conn.execute(sql);
        
        Object obj = convert(rs);
        return obj;
    }

    
    Object convert(ResultSet rs) {
        std::vector<std::string> data = rs.get_data();
        std::string name = data[0];
        Object obj(name);
        return obj;
    }
};


class NewDB {
public:
    
    ResultSet query(std::string new_grammar) {
        
        
        Connection conn;
        ResultSet rs = conn.execute(new_grammar);
        return rs;
    }
};


class Adapter {
private:
    
    NewDB* new_db;
public:
    
    Adapter(NewDB* new_db) {
        this->new_db = new_db;
    }

    
    Object query(std::string sql) {
        std::string new_grammar = translate(sql);
        ResultSet rs = new_db->query(new_grammar);
        Object obj = convert(rs);
        return obj;
    }

    
    std::string translate(std::string sql) {
        
        
        std::vector<std::string> tokens = split(sql, ' ');
        std::swap(tokens[0], tokens[2]);     
        std::string new_grammar = join(tokens, ' ');
        return new_grammar;
    }

    
    Object convert(ResultSet rs) {
        std::vector<std::string> data = rs.get_data();
        std::string name = data[0];
        Object obj(name);
        return obj;
    }

    
    std::vector<std::string> split(std::string s, char delim) {
        std::vector<std::string> tokens;
        std::string token;
        for (char c : s) {
            if (c == delim) {
                tokens.push_back(token);
                token = "";
            } else {
                token += c;
            }
        }
        tokens.push_back(token);
        return tokens;
    }

    
    std::string join(std::vector<std::string> tokens, char delim) {
        std::string s;
        for (int i = 0; i < tokens.size(); i++) {
            s += tokens[i];
            if (i < tokens.size() - 1) {
                s += delim;
            }
        }
        return s;
    }
};


int main() {
    ORM orm;
    NewDB new_db;
    Adapter adapter(&new_db);

    Object obj1 = orm.query("SELECT * FROM table");
    Object obj2 = adapter.query("SELECT * FROM table");
    
    if (obj1 == obj2) {
        std::cout << "The adapter works!" << std::endl;
    } else {
        std::cout << "The adapter fails!" << std::endl;
    }
}

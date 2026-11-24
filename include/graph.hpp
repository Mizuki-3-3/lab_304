#pragma once
#include "hash_table.hpp"

template <typename Vertex_type, typename Weight = size_t>
class graph{
    using T = Vertex_type;
public:
virtual bool add(T from, T to, Weight weight_) = 0;
virtual bool remove() = 0;
};

//если в хеш таблице нет пути из а в b, то вес а->b равен бесконечности
template <typename Vertex_type, typename Weight = size_t>
class directed_graph:graph<Vertex_type, Weight>{
    using T = Vertex_type;
    hash_table<Weight, pair<T, T>> adjacency_list;
public:
    directed_graph(): adjacency_list(){}
    directed_graph(const directed_graph& other): adjacency_list(other.adjacency_list){}
    directed_graph& operator=(const directed_graph& other){
        adjacency_list=other.adjacency_list;
        return *this;
    }

    directed_graph(directed_graph&& other): adjacency_list(std::move(other.adjacency_list)){}
    directed_graph& operator=(directed_graph&& other){
        std::swap(adjacency_list, other.adjacency_list);
        return *this;
    }

    bool add(T from, T to, Weight weight_) override{
        return adjacency_list.insert(pair<T,T>(from, to), weight_);
    }

    bool remove(const T from, const T to)override{
        if (from == to){return adjacency_list.remove(pair<T, T>(from, to));}
        return adjacency_list.remove(pair<T, T>(from, to)) && adjacency_list.remove(pair<T, T>(to, from));
    }
    
};

template <typename Vertex_type, typename Weight = size_t>
class undirected_graph:graph<Vertex_type, Weight>{
    using T = Vertex_type;
    hash_table<Weight, pair<T, T>> adjacency_list;
public:
    undirected_graph(): adjacency_list(){}
    undirected_graph(const undirected_graph& other): adjacency_list(other.adjacency_list){}
    undirected_graph& operator=(const undirected_graph& other){
        adjacency_list=other.adjacency_list;
        return *this;
    }

    undirected_graph(undirected_graph&& other): adjacency_list(std::move(other.adjacency_list)){}
    undirected_graph& operator=(undirected_graph&& other){
        std::swap(adjacency_list, other.adjacency_list);
        return *this;
    }

    bool add(const T from, const T to, Weight weight_)override{
        if (from==to){return adjacency_list.insert(pair<T,T>(from, to), weight_);}
        return adjacency_list.insert(pair<T,T>(from, to), weight_) && adjacency_list.insert(pair<T,T>(to, from), weight_); 
    }

    bool remove(const T from, const T to)override{
        if (from == to){return adjacency_list.remove(pair<T, T>(from, to));}
        return adjacency_list.remove(pair<T, T>(from, to)) && adjacency_list.remove(pair<T, T>(to, from));
    }
    
};




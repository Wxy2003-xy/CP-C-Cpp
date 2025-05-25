#include <bits/stdc++.h>
using namespace std;
template<typename Alphabet>
struct State {
    int id;
    bool operator==(State o) const noexcept { return id==o.id; }
    bool operator<(State o) const noexcept { return id<o.id; }
    State(int id_) : id(move(id_)) {} 
};
namespace std {
  template<typename Alphabet>
  struct hash<State<Alphabet>> {
    size_t operator()(State<Alphabet> s) const noexcept
      { return std::hash<int>()(s.id); }
  };
}
template<typename Alphabet>
class DFA {
    public: 
        using StateT = State<Alphabet>;
        using Trans = unordered_map<Alphabet,StateT>;
        set<StateT> Q;
        set<Alphabet> S;
        unordered_map<StateT, Trans> D;
        StateT q_0;
        set<StateT> F;
        DFA(set<StateT> Q_, set<Alphabet> S_, 
            unordered_map<StateT, Trans> D_, 
            StateT q0, set<StateT> F_) : Q(move(Q_)), S(move(S_)), 
            D(move(D_)), q_0(move(q0)), F(move(F_)) {}
        DFA() = default;
        bool test(vector<Alphabet> s) {
            StateT curr = q_0;
            for (Alphabet a : s) {
                auto it = D.find(curr);
                if (it == D.end()) {
                    return false;
                }
                auto& outgoing = it->second;
                auto ait = outgoing.find(a);
                if (ait==outgoing.end()) {
                    curr = outgoing.find(a);
                } else {
                    return false;
                }
            }
            return this->F.count(curr) > 0;
        }

};

class NFA {

};


int main() {
    State<char> q0 = State<char>(0);
    State<char> q1 = State<char>(1);
    State<char> q2 = State<char>(2);
    State<char> q3 = State<char>(3);
    set<State<char>> Q = {q0, q1, q2, q3};

    set<char> Q = {};
    DFA<char> dfa = DFA<char>();

    return 0;
}
template <class Object>
class MatNode
{
protected:
   int col;

public:
   Object data;

   MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {} 
   int getCol() const { return col; }
   
   // not optimized yet for set() = defaultVal;  refer to forums
   const Object & operator=(const Object &x);
};

template <class Object>
const Object & MatNode<Object>::operator=(const Object &x) {
   return (data = x); 
}
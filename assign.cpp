struct Point
{
	int x,y,z;
	public Point(int x,int y,int h):x(x),y(y),h(h)
        {  
        }
}
struct Node
{
            Point p;
            Node * Left;
            Node *  Right;
            public Node(Node n)
            {
                p = n;
		left=null;
		right=null;
            }
	    
}
class Tree2D
{
	Node rootNode = null;
        public Tree2D(Point[] points)
       {
            if (points != null)
            {
                foreach (Point p in points)
                    Insert(p);
            }
        }
        public void Insert(Point p)
        {
            Node current        = rootNode;
            Node previous       = null;
            bool useX           = false;
            bool useLeftSubtree = false;
            while (current != null)
            {
                // Should we explore the right subtree or the left subtree ?
                useLeftSubtree = useX ? (p.X < current.Point.X) : (p.Y < current.Point.Y);                
                previous = current;
                current  = useLeftSubtree ? current.Left : current.Right;
                useX     = !useX;
            }
            // Insert the node
            if (rootNode == null)
                rootNode = Node(p);
            else
            {
                if (useLeftSubtree)
                    previous.Left  =Node(p);
                else
                    previous.Right =Node(p);
            }

        }
        public ArrayList Pick(Rectangle rect)
        {
            ArrayList pointsFound = new ArrayList();
            RecursivePick(rootNode, rect, false, pointsFound);
            return pointsFound;

        }        
        private void RecursivePick(Node rootNode, Rectangle rect, bool useX, ArrayList pointsFound)
        {
            if (rootNode == null)
                return; 
            // Should we analyze the left subtree and/or the right subtree ?
            bool analyzeLeftSubTree  = useX ? (rect.Left < rootNode.Point.X):(rect.Top < rootNode.Point.Y);
            bool analyzeRightSubTree = useX ? (rootNode.Point.X <= rect.Right):(rootNode.Point.Y <= rect.Bottom); 

            // Analyze the left subtree
            if (analyzeLeftSubTree)
                RecursivePick(rootNode.Left, rect, !useX, pointsFound);
            // If the point is inside the rectangle, add it to the result list
            if (rect.Contains(rootNode.Point))
                pointsFound.Add(rootNode.Point);

 

            // Analyze the right subtree

            if (analyzeRightSubTree)

                RecursivePick(rootNode.Right, rect, !useX, pointsFound);

        }

}

 



 

Tree2D    tree2D      = new Tree2D(points);

ArrayList pointsFound = tree2D.Pick(new Rectangle(e.X - pickRadius,

  e.Y - pickRadius,

  2 * pickRadius,

  2 * pickRadius));

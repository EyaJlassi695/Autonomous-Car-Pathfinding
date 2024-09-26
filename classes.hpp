#ifndef CLASSES_HPP_INCLUDED
#define CLASSES_HPP_INCLUDED

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cfloat>
#include <cmath>
#include <algorithm>

using namespace std;

class Sommet {
public:
    double x, y;
    double angle;

    Sommet(double x_ = 0., double y_= 0., double a_ = 0.) : x(x_), y(y_), angle(a_) {}

    Sommet& operator=(const Sommet& other) {
        if (this != &other) {  // Check for self-assignment
            x = other.x;
            y = other.y;
            angle = other.angle;
        }
        return *this;
    }

    // Equality operator
    bool operator==(const Sommet& other) const {
        return (fabs(x - other.x) < (max(fabs(x),fabs(other.x))/pow(10,6))) && (fabs(y - other.y) < (max(fabs(y),fabs(other.y))/pow(10,6)));
    }
    friend ostream& operator<<(ostream& out, const Sommet& s){
        out<<"("<<s.x<<','<<s.y<<")";
        return out;
    }
};


class Segment {
public:
    Sommet start_Sommet, end_Sommet;

    Segment(const Sommet& start, const Sommet& end) : start_Sommet(start), end_Sommet(end) {}
};


class Obstacle {
public:
    std::vector<Sommet> vertices;


    Obstacle(const std::vector<Sommet>& vertices_, const double& eps, const bool& padding= true) {
        if(Sens_Positive(vertices_, eps)) {
            if(padding) vertices = with_Padding(vertices_, eps);
            else vertices = vertices_;
        } else {
            vector<Sommet> inv_vertices = vertices_;
            reverse(inv_vertices.begin(),inv_vertices.end());
            if(padding) vertices = with_Padding(inv_vertices, eps);
            else vertices = inv_vertices;
        }
    }

    bool intersectionWithSegment(const Segment& segment, const double& eps) {
        // Détection d'intersection entre le segment et l'obstacle
        //double eps = max(fabs(segment.start_Sommet.y),fabs(segment.start_Sommet.x)) / pow(10,6);
        double m_segment,b_segment;
        if(fabs(segment.end_Sommet.x - segment.start_Sommet.x)>eps) {
            m_segment = (segment.end_Sommet.y - segment.start_Sommet.y) / (segment.end_Sommet.x - segment.start_Sommet.x);
            b_segment = segment.end_Sommet.y - m_segment * segment.end_Sommet.x;
        } else {
            m_segment = 0;
            b_segment = segment.end_Sommet.y;
        }
        int found = 0; bool first_Found = false;
        for(int i=0; i<vertices.size();i++) {
            if(found == 1) {
                found =2;
            } else {
                //cout<<vertices[i].y - m_segment * vertices[i].x - b_segment<<'\n';
                if(fabs(vertices[i].y - m_segment * vertices[i].x - b_segment) < eps) {
                    if( ((vertices[i].y < segment.end_Sommet.y+(eps/3)) && (vertices[i].y > segment.start_Sommet.y-(eps/3)))
                        || ((vertices[i].y > segment.end_Sommet.y-(eps/3)) && (vertices[i].y < segment.start_Sommet.y+(eps/3))) ) {
                            found++;
                            //cout<<"found: "<<vertices[i]<<'\n';
                            if(i==0) first_Found=true;
                            else if(i==(vertices.size()-1) && first_Found) found =2;
                        }
                }
            }
            int j = (i==(vertices.size()-1))? 0:i+1;
            double x,y;
            if(fabs(vertices[j].x - vertices[i].x)<1e-4) {
                x = vertices[i].x;
                y = m_segment *x +b_segment;
            }
            else if(fabs(segment.end_Sommet.x - segment.start_Sommet.x)>eps){
                double m = (vertices[j].y - vertices[i].y) / (vertices[j].x - vertices[i].x);
                double b = vertices[i].y - m * vertices[i].x;
                x = (b_segment - b) / (m - m_segment);
                if(fabs(m - m_segment) < eps) continue;
                y = m * x + b;
            } else {
                x=segment.end_Sommet.x;
                double m = (vertices[j].y - vertices[i].y) / (vertices[j].x - vertices[i].x);
                double b = vertices[i].y - m * vertices[i].x;
                y = m * x + b;
            }
            //cout<<x<<' '<<y<<'\n';
            if(SegmentIntersect(Sommet(x,y), Segment(vertices[i],vertices[j]), eps) && SegmentIntersect(Sommet(x,y), segment, eps)) {
                /*cout<<x<<' '<<y<<'\n';
                cout<<vertices[i]<<'\n';
                cout<<vertices[j]<<'\n';*/
                return true;
            }

        }
        return (found == 3);
    }
private:

    bool SegmentIntersect(const Sommet& s, const Segment& seg, const double& eps) {
        //double eps = max(fabs(s.x),fabs(s.y)) / pow(10,6);
        if( ((s.y < (seg.end_Sommet).y-(eps/3)) && (s.y > (seg.start_Sommet).y+(eps/3)))
                || ((s.y > (seg.end_Sommet).y+(eps/3)) && (s.y < (seg.start_Sommet).y-(eps/3))) ) return true;
            else if(fabs((seg.end_Sommet).y - (seg.start_Sommet).y) < eps) {
                if( ((s.x < (seg.end_Sommet).x-(eps/3)) && (s.x > (seg.start_Sommet).x+(eps/3)))
                || ((s.x > (seg.end_Sommet).x+(eps/3)) && (s.x < (seg.start_Sommet).x-(eps/3))) ) return true;
            }
        return false;
    }
    vector<Sommet> with_Padding(const std::vector<Sommet>& vertices_, const double& eps) {
        vector<Sommet> Curr_vertices_ = vertices_, vertices;
        for(int b=0; b<Curr_vertices_.size();b++) {
            int c = (b==Curr_vertices_.size()-1)? 0:b+1;
            int a = (b==0)? Curr_vertices_.size()-1:b-1;
            Sommet s1 = Curr_vertices_[a], s2 = Curr_vertices_[b], s3 = Curr_vertices_[c];

            //double eps = max(max(fabs(s1.x),fabs(s1.y)),max(fabs(s2.x),fabs(s2.y))) / pow(10,6);
            double pad = eps * 2 * pow(10,4);
            double ang1, ang2;
            if(fabs(s2.x - s1.x) < eps) ang1 = (s2.y >= s1.y)? (M_PI/2): (-1)*(M_PI/2);
            else {
                ang1 = atan((s2.y - s1.y)/(s2.x - s1.x));
                if((s2.x - s1.x)<0) ang1 += M_PI;
            }
            if(fabs(s3.x - s2.x) < eps) ang2 = (s2.y >= s3.y)? (M_PI/2):(-1)*(M_PI/2);
            else {
                ang2 = atan((s2.y - s3.y)/(s2.x - s3.x));
                if((s2.x - s3.x)<0) ang2 += M_PI;
            }

            double angdiff = ang1-ang2;
            while(angdiff<0) angdiff+=2*M_PI;
            while(angdiff>2*M_PI) angdiff-=2*M_PI;
            double ang = ang1-angdiff/2;

            vertices.push_back(Sommet(s2.x+pad*cos(ang)/sin(angdiff/2),s2.y+pad*sin(ang)/sin(angdiff/2)));
        }
        return vertices;
    }
    bool Sens_Positive(const std::vector<Sommet>& vertices_, const double& eps) {
        double somme_Ang=0;
        long long unsigned int n = vertices_.size();
        for(long long unsigned int b=0;b<n;b++) {
            long long unsigned int a = (b==0)? n-1:b-1;
            long long unsigned int c = (b==n-1)? 0:b+1;
            Sommet s1 = vertices_[a], s2 = vertices_[b], s3 = vertices_[c];

            //double eps = max(max(fabs(s1.x),fabs(s1.y)),max(fabs(s2.x),fabs(s2.y))) / pow(10,6);

            double ang1,ang2;
            if(fabs(s2.x - s1.x) < eps) ang1=(s2.y - s1.y)?(M_PI/2):(-1)*(M_PI/2);
            else {
                ang1 = atan((s2.y - s1.y)/(s2.x - s1.x));
                if((s2.x - s1.x)<0) ang1 += M_PI;
            }
            if(fabs(s3.x - s2.x) < eps) ang2=(s3.y - s2.y)?(M_PI/2):(-1)*(M_PI/2);
            else {
                ang2 = atan((s3.y - s2.y)/(s3.x - s2.x));
                if((s3.x - s2.x)<0) ang2 += M_PI;
            }

            double angdiff = ang2-ang1;
            while(angdiff<-M_PI) angdiff+=2*M_PI;
            while(angdiff>M_PI) angdiff-=2*M_PI;
            somme_Ang+=angdiff;
        }
        //cout<<somme_Ang<<'\n';
        return (somme_Ang>0);
    }
};

class Arcs : public Segment
{
public:
    double length;

    Arcs(const Sommet& start, const Sommet& end) : Segment(start, end) {
        double diff_angle = fabs(end.angle - start.angle);
        while(diff_angle >= (M_PI*2)) diff_angle -= (M_PI * 2);
        diff_angle = diff_angle<(2*M_PI-diff_angle)?diff_angle:(2*M_PI-diff_angle);
        //if(isnan(diff_angle)) cout<<end.angle<<' '<<start.angle<<'\n';
        length = sqrt(pow(start.x - end.x,2) + pow(start.y - end.y,2) + pow(diff_angle,2));
    }
};

class Graph {
public:
    vector<Arcs> arcs;

    Graph(const vector<Arcs>& first_arc = {}) : arcs(first_arc) {}
    void AddArc(const Arcs& arc) {
        arcs.push_back(arc);
    }
};

class arc_planification: public Graph
{
public:
    Sommet start_Sommet, end_Sommet;
    vector<Obstacle> obstacles;
    double epsilon;

    arc_planification(const Graph& graph, const Sommet& start, const Sommet& end, const vector<Obstacle>& obs, const double& eps)
        : Graph(graph), start_Sommet(start), end_Sommet(end), obstacles(obs), epsilon(eps) {
            for(long long unsigned int i=0;i<obstacles.size();i++) {
                for(auto iter = arcs.begin(); iter < arcs.end();) {
                    if((obstacles[i]).intersectionWithSegment(*iter, eps)) {
                       iter = arcs.erase(iter);
                    } else ++iter;
                }
            }
            int n=arcs.size();
            for(int i=0; i<n; i++) {
                Arcs interm(arcs[i].end_Sommet, arcs[i].start_Sommet);
                (*this).AddArc(interm);
            }
        }

    void AddAngles() {
        vector<pair<Sommet,Sommet>> new_Sommets;
        for(auto iter=arcs.begin();iter<arcs.end();iter++) {
            double angle;
            if(fabs(iter->end_Sommet.x - iter->start_Sommet.x)< max(fabs(iter->end_Sommet.x),fabs(iter->start_Sommet.x))/pow(10,6)) {
                if(iter->end_Sommet.y - iter->start_Sommet.y > 0) angle = (M_PI/2);
                else angle = - (M_PI/2);
            } else {
                angle = atan((iter->end_Sommet.y-iter->start_Sommet.y)/(iter->end_Sommet.x-iter->start_Sommet.x));
            }
            new_Sommets.push_back(make_pair(Sommet(iter->start_Sommet.x, iter->start_Sommet.y, angle),iter->end_Sommet));
        }
        vector<Arcs> new_Arcs;
        for(auto iter=new_Sommets.begin(); iter<new_Sommets.end();iter++) {
            for(int i=0;i<arcs.size();i++) {
                if(iter->first == (arcs[i]).start_Sommet && iter->second == (arcs[i]).end_Sommet) {
                    for(auto iter2=new_Sommets.begin(); iter2<new_Sommets.end();iter2++) {
                        if(iter2->first == iter->second)
                            new_Arcs.push_back(Arcs(iter->first,iter2->first));
                    }
                }
            }
        }
        arcs = new_Arcs;
    }

    vector<Sommet> trouverCheminMinimal(const bool& dynamic = true) {
        // Utilisation de l'algorithme de Dijkstra pour trouver le chemin minimal
        vector<Sommet> Sommets = listnodes();
        int n = Sommets.size();
        double poids[n];
        for (int i = 1; i < n; ++i) poids[i] = FLT_MAX;
        poids[0] = 0.;
        vector<int> X;
        vector<int> E;
        for(int i =0;i<n;i++) {
            X.push_back(i);
        }

        int p[n];
        vector<pair<int,int>> Succ[n];
        for(int i = 0; i<n ; i++) {
            for(auto iter = arcs.begin(); iter < arcs.end(); iter++){
                if(iter->start_Sommet == Sommets[i]) {
                    for(int j=0; j<n;j++) {
                        if(Sommets[j] == iter->end_Sommet) {
                            Succ[i].push_back({j,iter->length});
                        }
                    }
                }
            }
        }
        while(!X.empty()) {
            double poids_min = FLT_MAX;
            int noeud_ind = 0, ind = 0, k=0;
            for(auto iter = X.begin(); iter < X.end();iter++) {
                if(poids_min > poids[*iter]) {
                    poids_min = poids[*iter];
                    noeud_ind = *iter;
                    ind =k;
                }
                k++;
            }
            E.push_back(noeud_ind);
            X.erase(X.begin() + ind);
            for(int i = 0;i<(Succ[noeud_ind]).size();i++) {
                if(isInX(Succ[noeud_ind][i],X)) {
                    if(poids[Succ[noeud_ind][i].first] > poids[noeud_ind] + Succ[noeud_ind][i].second) {
                        poids[Succ[noeud_ind][i].first] = poids[noeud_ind] + Succ[noeud_ind][i].second;
                        p[Succ[noeud_ind][i].first] = noeud_ind;
                    }
                }
            }
        }
        vector<Sommet> result;
        int CurrNode = 1;
        result.push_back(Sommets[CurrNode]);
        while(CurrNode != 0) {
            CurrNode = p[CurrNode];
            result.push_back(Sommets[CurrNode]);
        }
        if(!dynamic) return result;
        else return result_dynamic(result, epsilon);

        /*for(int i =0; i<arcs.size(); i++) {
            cout << "[("<< (arcs[i]).start_Sommet.x<< ',' << (arcs[i]).start_Sommet.y << "),";
            cout << '('<< (arcs[i]).end_Sommet.x<< ',' << (arcs[i]).end_Sommet.y<<")],\n";

        } cout <<endl;*/
    }



private:
    vector<Sommet> listnodes() {
        vector<Sommet> Sommets;
        Sommets.push_back(start_Sommet);
        Sommets.push_back(end_Sommet);
        for(auto iter = arcs.begin(); iter < arcs.end(); iter++){
            bool start_Found = false, end_Found = true;
            for(int i=0;i<Sommets.size();i++) {
                if(Sommets[i] == iter->start_Sommet) {
                    start_Found=true;
                } else if(Sommets[i] == iter->end_Sommet) {
                    end_Found=true;
                }
            }
            if(!start_Found) Sommets.push_back(Sommet((iter->start_Sommet).x,(iter->start_Sommet).y));
            if(!end_Found) Sommets.push_back(Sommet((iter->end_Sommet).x,(iter->end_Sommet).y));

        }
        /*for(int i=0;i<obstacles.size();i++) {
            for(auto iter = (obstacles[i]).vertices.begin(); iter <(obstacles[i]).vertices.end(); iter++) {
                Sommets.push_back(*iter);
            }
        }*/
        return Sommets;
    }

    bool isInX (pair<int,int>& elem, vector<int>& X) {
        for(int i=0; i<X.size();i++) {
            if(elem.first == X[i]) return true;
        }
        return false;
    }
    vector<Sommet> result_dynamic(vector<Sommet> result, const double& eps) {
            double pad = eps * 5 * pow(10,4);
            //Drift au début
            Sommet A = result.back();
            result.pop_back(); Sommet A1=result.back();
            int signe = A1.y>=A.y?-1:1;
            result.push_back(Sommet(A.x+pad,A.y-signe*.5*pad)); result.push_back(A);
            int n = result.size();

            vector<Sommet> result_Physique;
            result_Physique.push_back(result.front());
            for(int b=1;b<n-1;b++) {
                Sommet s1 = result[b-1], s2 = result[b], s3 = result[b+1];

                double ang1,ang2;
                if(fabs(s2.x - s1.x) < eps) ang1=(s2.y - s1.y)?0:(-1)*M_PI;
                else {
                    ang1 = atan((s2.y - s1.y)/(s2.x - s1.x)) - (M_PI/2);
                    if((s2.x - s1.x)<0) ang1 += M_PI;
                }
                if(fabs(s3.x - s2.x) < eps) ang2=(s3.y - s2.y)?0:(-1)*M_PI;
                else {
                    ang2 = atan((s3.y - s2.y)/(s3.x - s2.x)) - (M_PI/2);
                    if((s3.x - s2.x)<0) ang2 += M_PI;
                }

                double angdiff = ang2-ang1;
                while(angdiff<-M_PI) angdiff+=2*M_PI;
                while(angdiff>M_PI) angdiff-=2*M_PI;

                if(angdiff<0) ang1 -= M_PI;

                double dis_angle = fabs(angdiff);
                //if(angdiff>0) dis_angle = min(ang2-ang1, 2*M_PI + ang1 - ang2);
                //else dis_angle = min(ang1-ang2, 2* M_PI + ang2 - ang1);
                //cout<< coor1<< ' ' << coor2 <<'\n';
                //cout<< ang1 *180/M_PI<< ' ' << (ang1+angdiff)*180/M_PI <<'\n';
                int n_angles = 10-int(dis_angle*(10/M_PI));

                Sommet s = Sommet(s2.x-pad*cos(ang1+angdiff/2), s2.y-pad*sin(ang1+angdiff/2));
                for(int i=0; i<=n_angles;i++) {
                    double ang = ang1 + (angdiff)*i/n_angles;
                    Sommet P = Sommet(s.x+pad*cos(ang),s.y+pad*sin(ang));
                    result_Physique.push_back(P);
                }
            }
            result_Physique.push_back(result.back());
            return result_Physique;
    }
};
#endif // CLASSES_HPP_INCLUDED

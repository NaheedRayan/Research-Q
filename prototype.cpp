#include<bits/stdc++.h>


using namespace std ;

map<string,string> mp_V ;
map<string,string> mp_V_plus ;



// const int ROW = 3 , COL = 6 ;
// vector<vector<string>>matrix { 
// {"-" , "down" , "CNOT"  ,"down"   , "-"   , "-" },
// {"-" , "|d"   , "up"    ,"|d"     , "down", "-" },
// {"-" , "V"    , "-"     ,"V+"     , "V"   , "-" }
// };  


const int ROW = 4 , COL = 8 ;
vector<vector<string>>matrix { 
{"-" , "-"   , "-"     ,"down"   , "-"   ,  "CNOT" , "down" , "-"},
{"-" , "-"   , "down"  ,"|d"     , "CNOT",  "up"   , "|d"   , "-"},
{"-" , "down", "|d"    ,"|d"     , "up"  ,  "-"    , "|d"   , "-"},
{"-" , "V"   , "V"     ,"V"      , "-"   ,  "-"    , "V+"   , "-"}
};  


// vector<vector<string>>value { 
// {"0" , "0" , "0"  ,"0" , "0", "0"},
// {"0" , "0" , "0"  ,"0" , "0", "0"},
// {"0" , "0" , "0"  ,"0" , "0", "0"}
// }; 

vector<vector<string>>value(ROW , vector<string>(COL , "0"));

void refresh_value_matrix()
{
    for(int i = 0 ; i < ROW ;i++)
        for(int j = 0 ; j < COL ;j++)
            value[i][j] = "0" ;
}

void print_data(){
    for(int i = 0 ; i < ROW ; i++ )
    {
        cout << "---" ;
        for(int j = 0 ; j < COL ; j++)
        {
            int len =  matrix[i][j].length();
            cout << matrix[i][j] ;
            for(int i = 0 ; i <  4 - len ;i++)
            cout << "-" ;
            cout << "----" ;
        }            
        cout << endl ;
    }
}

void print_value(){
    for(int i = 0 ; i < ROW ; i++ )
    {
        cout << "---" ;
        for(int j = 0 ; j < COL ; j++)
        {
            int len =  value[i][j].length();
            cout << value[i][j] ;
            for(int i = 0 ; i <  4 - len ;i++)
            cout << "-" ;
            cout << "----" ;
        }            
        cout << endl ;
    }
}

void crawl(int i , int j , string state , int main_branch){

    if(i >= ROW || j >= COL || i < 0 || i >= ROW || j < 0 || j >= COL)
        return ;

    

    if(matrix[i][j] == "-")
    {
        value[i][j] =  state;

        // going to the right
        if(j+1 <COL)
        {
            if(matrix[i][j+1] == "|u" || matrix[i][j+1] == "|d" )
                crawl(i , j+1 , state , 0 ) ;
            else    
                crawl(i , j+1 , state , 1 ) ;
        }
         
        // if((i+1 < ROW && i+1 >= 0)&& i>0)
        // {
        //     cout << "heoo" ;
        //     if(matrix[i+1][j] == "up")
        //         crawl(i+1 , j , state, 0) ;
        // }
        // if((i-1 < ROW && i-1 >= 0)&& i < ROW-1)
        // {
        //     cout << "wow";
        //     if(matrix[i-1][j] == "down")
        //         crawl(i-1 , j , state , 0) ;
        // }

    }
    else if(matrix[i][j] == "CNOT")
    {
        if(value[i][j] == "1")
        {    

            if(state == "0")
                state = "1" ;
            else state = "0" ;

                
            if(j+1 <COL && main_branch!=0)
            {
                if(matrix[i][j+1] == "|u" || matrix[i][j+1] == "|d" )
                    crawl(i , j+1 , state , 0 ) ;
                else    
                    crawl(i , j+1 , state , 1 ) ;
            }
        }
        else
        {

                
            if(j+1 <COL && main_branch!=0)
            {
                if(matrix[i][j+1] == "|u" || matrix[i][j+1] == "|d" )
                    crawl(i , j+1 , state , 0 ) ;
                else    
                    crawl(i , j+1 , state , 1 ) ;
            }

            // if((i+1 < ROW && i+1 >= 0)&& i>0)
            // {
            //     cout << "heoo" ;
            //     if(matrix[i+1][j] == "up")
            //         crawl(i+1 , j , state , 0) ;

            // }
            // if((i-1 < ROW && i-1 >= 0)&& i < ROW-1)
            // {
            //     cout << "wow";
            //     if(matrix[i-1][j] == "down")
            //         crawl(i-1 , j , state , 0) ;

            // }
            // crawl(i , j+1 , state) ;
            // value[i][j] = state;


        }
        
    }
    
    else if(matrix[i][j] == "down")
    {
        

        value[i][j] = state;
        if((i+1 < ROW && i+1 >= 0))        
        {
            if(matrix[i+1][j] == "|d" )
            {
                crawl(i+1 , j , state , 1) ;
            }
            else if(matrix[i+1][j] == "CNOT")
            {
                value[i+1][j] = state;
                crawl(i+1 , j , state , 0) ;
            }
            else if(matrix[i+1][j] == "V")
            {
                value[i+1][j] = state;
                // crawl(i+1 , j , state , 0) ;
            }
            else if(matrix[i+1][j] == "V+")
            {
                value[i+1][j] = state;
                // crawl(i+1 , j , state , 0) ;
            }
        }
    
       
        if(j+1 <COL)
        {
            
            if(matrix[i][j+1] == "|u" || matrix[i][j+1] == "|d" )
            {
                crawl(i , j+1 , state , 0 ) ;
            }
            else
            {    
                crawl(i , j+1 , state , 1 ) ;
            }
        }

    }
    else if(matrix[i][j] == "up")
    {

        value[i][j] = state;
        if((i-1 < ROW && i-1 >= 0))        
        {
            if(matrix[i-1][j] == "|u" )
                crawl(i-1 , j , state , 1) ;
            else if(matrix[i-1][j] == "CNOT")
            {
                value[i-1][j] = state;
                crawl(i-1 , j , state , 0) ;
            }
            else if(matrix[i-1][j] == "V")
            {
                value[i-1][j] = state;
                // crawl(i-1 , j , state , 0) ;
            }
            else if(matrix[i-1][j] == "V+")
            {
                value[i-1][j] = state;
                // crawl(i-1 , j , state , 0) ;
            }
        }
        if(j+1 <COL)
        {
            if(matrix[i][j+1] == "|u" || matrix[i][j+1] == "|d" )
                crawl(i , j+1 , state , 0 ) ;
            else    
                crawl(i , j+1 , state , 1 ) ;
        }
    }
    else if(matrix[i][j] == "|d")
    {    
        if(main_branch == 1  && matrix[i+1][j] == "|d")
        {
            crawl(i+1 , j , state , 1) ;
        }
        else if(main_branch == 1 && (matrix[i+1][j] == "V" || matrix[i+1][j] == "V+") )
        {
            value[i+1][j] = state ;
            // crawl(i+1 , j , state , 0) ;
        }
        else if(main_branch == 0){
            crawl(i , j+1 , state , 1) ;
        }
    }
    else if(matrix[i][j] == "|u")
    {
        if(main_branch == 1 && matrix[i-1][j] == "|u")
        {
            crawl(i-1 , j ,state , 1) ;
        }
        else if(main_branch == 1 && (matrix[i-1][j] == "V" || matrix[i-1][j] == "V+") )
        {
            value[i-1][j] = state ;
            // crawl(i-1 , j , state , 0) ;
        }
        else if(main_branch == 0){
            crawl(i , j+1 , state , 1) ;
        }
    }
    else if(matrix[i][j] == "V")
    {
        if(main_branch == 1 && value[i][j] == "1")
        {
            // cout << "Inside  v "<<state <<endl ;
            
            state = mp_V[state] ;
            // value[i][j] = state;
            crawl(i , j+1 , state , 1) ;
        }
        else
        {
            // cout << "Inside else in v "<<state <<endl ;

            // value[i][j] = state;
            crawl(i , j+1 , state , 1) ;
        }
    }
    else if(matrix[i][j] == "V+")
    {
        if(main_branch == 1 && value[i][j] == "1")
        {
            cout << "Inside  v+ "<<state <<endl ;
            


            state = mp_V_plus[state] ;
            // value[i][j] = state;
            // value[i][j+1] = state;
            crawl(i , j+1 , state , 1) ;
        }
        else
        {
            cout << "Inside else in v+ "<<state <<endl ;

            // value[i][j] = state;
            // value[i][j+1] = state;
            crawl(i , j+1 , state , 1) ;
        }
    }


}

int main(){

    // create_value_matrix() ;

    // refresh_value_matrix();
    // print_value();

    mp_V.insert({"0" , "v"});
    mp_V.insert({"1" , "V"});
    mp_V.insert({"v" , "1"});
    mp_V.insert({"V" , "0"});
    mp_V.insert({"w" , "0"});
    mp_V.insert({"W" , "1"});


    mp_V_plus.insert({"0" , "w"});
    mp_V_plus.insert({"1" , "W"});
    mp_V_plus.insert({"v" , "0"});
    mp_V_plus.insert({"V" , "1"});
    mp_V_plus.insert({"w" , "1"});
    mp_V_plus.insert({"W" , "0"});


    print_data();

    // for(int i = 0 ; i < 5 ;i++)
    // {
    //     crawl(0 , 0 , "0" , 1);
    //     crawl(1 , 0 , "1" , 1);
    //     crawl(2 , 0 , "0" , 1);

    // }
    // crawl(1 , 0 , "1" , 1);
    // crawl(0 , 0 , "1" , 1);
    // crawl(2 , 0 , "0" , 1);


    // for(int i = 0 ; i < 5 ;i++)
    // {
    //     crawl(0 , 0 , "1" , 1);
    //     crawl(1 , 0 , "0" , 1);
    //     crawl(2 , 0 , "1" , 1);
    //     crawl(3 , 0 , "0" , 1);

    // }

    crawl(2 , 0 , "1" , 1);
    crawl(1 , 0 , "0" , 1);
    crawl(0 , 0 , "1" , 1);
    crawl(3 , 0 , "0" , 1);

    cout << endl ; 
    print_value();

  
    
    
    return 0;
}
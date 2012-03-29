/* 
 * (c) Copyright 2009 Joaquim Pedro França Simão (osmano807) <osmano807@gmail.com>. Some Rights Reserved. 
 * @autor Joaquim Pedro França Simão (osmano807) <osmano807@gmail.com> 
 */

#include <iostream>
#include <cstring>
#include <vector>
#include "../utils.cpp"

// use this line to compile
// g++ -I. -fPIC -shared -g -o avast.com.so avast.com.cpp  

string get_filename(string url) {
		vector<string> resultado;
		if (url.find("?") != string::npos) {
			stringexplode(url, "?", &resultado);
			stringexplode(resultado.at(resultado.size()-2), "/", &resultado);
			return resultado.at(resultado.size()-1);           
		} else {
			stringexplode(url, "/", &resultado);
			return resultado.at(resultado.size()-1);
		}
}

extern "C" resposta getmatch(const string url) {
    resposta r;
	
	
	if ( (url.find(".avast.com/") != string::npos)   and
		 ( (url.find(".vpu") != string::npos) or (url.find(".smtap") != string::npos) ) and 
		   (url.find("servers.def.vpu") == string::npos) // this catch servers.def.vpu.smtap too
	) {
		
	    r.file = get_filename(url);
		if (!r.file.empty()) {
			r.match = true;
			r.domain = "avast";
		} else {
			r.match = false;
		}
	} else {
		r.match = false;
	}
	return r;
}
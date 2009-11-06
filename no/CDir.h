/*
 * CDir.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CDIR_H_
#define CDIR_H_

#include <vector>
#include <string>
using namespace std;

class TiXmlElement;
class CImage;

class CDir {
public:

	~CDir();
	bool 			Load(TiXmlElement* pXMLData);
	string 			GetName(){return m_Name;};
	CImage*			GetImage(int numImage){return m_Image.at(numImage);};
	int				GetMaxImages();

private:

	string				m_Name;
	vector<CImage* >	m_Image;

};

#endif /* CDIR_H_ */

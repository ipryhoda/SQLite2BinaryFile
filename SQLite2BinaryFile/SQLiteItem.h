#ifndef  _SQLLITE_ITEM_H
#define  _SQLLITE_ITEM_H

class ISQLiteItem
{
	ISQLiteItem(const ISQLiteItem&);
	ISQLiteItem& operator=(const ISQLiteItem&);
public:
	virtual ~ISQLiteItem() = 0;
};

#endif // _SQLLITE_ITEM_H

// room: /d/xingxiu/tianroad6.c
inherit ROOM;
#include <ansi.h>;
string look_wind();
int lian(string arg);
void create()
{
	set("short", "��ɽ����");
	set("long", @LONG
��������ɽ���塣����������Χ��ȥ�����׶���ԭ�ķ�⾡���۵ס�����
һ��С·������ɽ��ɽ��(wind)��������Ϊǿ���������޷�վ����
LONG
	);
	set("exits", ([
	    "eastdown" : __DIR__"tianroad5",
	]));
	set("item_desc", ([
	    "����ڡ�" : (: look_wind :),
	]));
	set("outdoors", "xingxiu");
	setup();
}

string look_wind()
{
	return "����һ�굽ͷ����ֹЪ�����Լ����麣�����磬����ζ��������ǳ���\n";
}

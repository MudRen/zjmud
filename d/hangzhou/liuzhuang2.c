// liuzhuang2.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��ׯ��Ժ");
	set("long", @LONG
��������ׯ�Աߵ�Ժ�ӣ����ߵ����ﲻ����Щ���棬��Ȼ���˼�
������������֮�˲��õ�����ľ�ˣ��Ա��м�����Ժ�Ҷ�ģ��������
��һ��ָ�ֻ��ŵĲ�֪����˵Щʲô��
LONG);
	set("exits", ([
	    "south" : __DIR__"liuzhuang",
	]));
	set("objects", ([
		__DIR__"npc/jiading" : 2,
		"/clone/npc/mu-ren" : 3,
	]));
	setup();
}


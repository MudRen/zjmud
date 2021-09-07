// tulu1.c
// Date: Nov.1997 by Venus

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
·��һ��СϪ��Ϫˮ���������ţ���ʱ�����(fish)Ծ��ˮ�档
Ϫ�Լ����к�������ͷר���ڵ��㡣
LONG);
	set("exits", ([
	    "southwest"     : __DIR__"shanlu5",
	    "northeast"     : __DIR__"maojiabu",
	]));

	set("objects", ([
	    __DIR__"npc/boy" : 2,
	]));

	set("item_desc", ([
		"fish" : "������һ������Ծˮ���������ۡ���һ��"
			 "�ֵ���ˮ������к�һ��ˮ��\n",
	]));

	set("resource/fish", ({ "/clone/fish/liyu",
				"/clone/fish/jiyu",
				"/clone/fish/qingyu",
				"/clone/fish/caoyu", }));

	set("outdoors", "hangzhou");
	setup();
}

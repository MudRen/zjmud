#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�ʹ����");
	set("long", @LONG
��������Ͻ��ǵ����ŵĴ�Ѱ�������ǵ������������ģ�������Բ�
������;������������ǸϿ��뿪Ϊ�á�
LONG NOR);
	set("exits", ([
		"north" : __DIR__"hgmen_n",
		"south" : __DIR__"hgmen_s",
		"west" : __DIR__"hg_w",
	]));
	set("objects", ([
		__DIR__"npc/yuqian1" : 2,
	]));
	set("outdoors", "beijing");
	setup();
}



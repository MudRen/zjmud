inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "�ʹ�����");
	set("long", @LONG
������ǻʹ��ı��ţ��ɸߵ������ų����ţ����Ͻ�ɫ��í���������⡣
��������վ�����������������������ͣ�Ĵ����Ź��������ˡ����õ�����ֱ
����Ρ����ΰ�Ĺų�ǽ�ϣ�ʹ�ó�ǽ�Ϸ����Ͻ��ǡ�����˸������Եø����
ҫ�ۡ������������������ǵ�������������ڻʹ����ŵ��������ࡣ�ӱ�����
���ذ��ſ��Ե��ﱱ���ı��ǽ���
LONG NOR);
	set("exits", ([
		"south" : __DIR__"hg",
		"north" : __DIR__"dianmen",
	]));
	set("objects", ([
		__DIR__"npc/bing2" : 1,
		__DIR__"npc/bing3" : 1,
		__DIR__"npc/yuqian1" : 1,
	]));
	set("no_fight", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	if (objectp(present("guan bing", environment(me))) && dir == "south")
		return notify_fail("��ǰ����������ס������˵�����ʹ��صأ�����Ѱ�����ճ��롣\n\n");
	return ::valid_leave(me, dir);
}

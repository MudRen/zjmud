inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "�ʹ�����");
	set("long", @LONG
������ǻʹ������ţ��ɸߵ������ų����ţ����Ͻ�ɫ��í���������⡣
��������վ�����������������������ͣ�Ĵ����Ź��������ˡ����õ�����ֱ
����Ρ����ΰ�Ĺų�ǽ�ϣ�ʹ�ó�ǽ�Ϸ����Ͻ��ǡ�����˸������Եø����
ҫ�ۡ����Ϸ��Ľ�ˮ�ſ��Դ�Խ���Ǻӵ��ﷱ�����찲�Ź㳡��
LONG NOR);
	set("exits", ([
		"south" : __DIR__"qiao",
		"north" : __DIR__"hg",
	]));
	set("objects", ([
		__DIR__"npc/bing2" : 2,
		__DIR__"npc/yuqian1" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if (objectp(present("guan bing", environment(me))) && dir == "north")
		return notify_fail(CYN "��ǰ����������ס������˵�����ʹ���"
				   "�أ�����Ѱ�����ճ��롣"NOR"\n");
	return ::valid_leave(me, dir);
}


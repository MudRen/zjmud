inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","����");
	set("long", @LONG
������Ǿ��ǵ�����������������������ں��ǿ��������ﾯ�����ϣ���
���Ʒ��Ķ����ٱ���̫�������������߶����������ﲻ�˾������Ͽ��뿪Ϊ�
LONG NOR);
	set("exits", ([
		"north" : __DIR__"dongchang_men",
	]));
	set("objects", ([
		__DIR__"npc/bing2" : 4,
		__DIR__"npc/taijian" : 1,
	]));
	set("no_fight", 1);
	setup();
}

//Room: jiulou2.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����¥��¥");
	set("long", 
"��¥�Ǿ�¥��������������Ŀ����Ƕ������������¥�µĿ���\n"
"�ǰ�����������¥���ľƲ�Ҳ������¥�Ƴ������ֵġ����Թ��ų���\n"
"ֱ���ݽǣ�\n"
HIR "       �������������ԾƸ߸裬����¥ͷ��������ͬ�֣�\n"
    "       ������һ�Σ��ٷ��յ���ƺὭ�ϣ����������\n\n"
NOR
	);

	set("exits", ([
		"down" : __DIR__"jiulou",
	]));
	set("objects", ([
		__DIR__"npc/yang-laoban" : 1,
	]));

	setup();
}

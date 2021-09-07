//Room: kzsleep.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "�͵�˯��");
	set("long", @LONG
��ջ��һ��˯�����������ɨ�øɸɾ�������ʱ�Ŀ��������Ӹ���
�ͷ��ﴫ�������Ĵ�����ǽ����һ�����������䣩���ǹ���������
Ϣ˯���õġ�
LONG
	);
	set("item_desc", ([ /* sizeof() == 1 */
		"bed" : "һ�Ű�ɫ����齣�����ȥ��Ϊ����(bed)��",
	]));
	set("exits", ([
		"down" : __DIR__"kezhan",
	]));

	set("no_fight", 1);
	setup();
}
void init()
{
	add_action("do_bed", "bed");
}
int do_bed()
{       object me;
	me=this_player();
	message_vision(HIY "$N�ƿ�ɴ�ʣ�׼���ϴ��ˡ�"NOR"\n", me);
	me->move(__DIR__"bed");
	message_vision(HIY "\nɳ������һ����$N���˽�����"NOR"\n", me);
	return 1;
}

int valid_leave(object me, string dir)
{
	me->delete_temp("rent_paid");
	return ::valid_leave(me, dir);
}

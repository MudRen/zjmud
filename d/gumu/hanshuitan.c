// hanshuitan.c ��ˮ̶
#include <ansi.h>
inherit BUILD_ROOM;
int do_qian(string arg);

void create()
{
	set("short", "��ˮ̶");
	set("long", @LONG
�����ǲݵصı�Ե������Ѿ���ϡ���ˣ���Ȼ��һ��������ص�
�ɹ�Ѱ��ʳ������ǰ��һ���岨�����Ĵ�ˮ̶ (tan)��ˮ���壬
��Լ���Լ���ˮ�׵Ĺ�ʯ��ᾣ�һ������ٿ�ش�ˮ���ι����ֲ�֪��
�㵽�Ŀ�ʯͷ�������ȥ�ˡ�����ӳ���£�ˮ�淺����һ����ɫ�ʺ磬
����������������������
LONG
	);
	set("outdoors", "gumu");
	set("max_room", 3);
	set("exits", ([
		"northwest" : __DIR__"caodi2",
	]));

	set("objects", ([
		__DIR__"npc/yufeng" : random(3),
	]));

	set("resource/water", 1);

	set("item_desc", ([
		"��ˮ̶��": "һ�ں����ˮ̶(tan)����֪���ɲ�����Ǳ(qian)�µ���ˮ������ȥ��\n"
			ZJOBACTS2"Ǳˮ:qian tan\n",
	]) );

	setup();
}

void init()
{
	add_action("do_qian", "qian");
}


int do_qian(string arg)
{
	object me=this_player();

	if (! arg || arg != "tan" )
		return notify_fail("��Ҫ������Ǳˮ��\n");

	message_vision(HIG"$N����һԾ������ˮ̯֮�У���������������ι���
������һ�̣�"NOR"\n",this_player());
	message_vision(HIG"ȴץ�˿ա�ͻȻ$N��ǰһ����һ�ɰ��������������$N
����һ�����ڡ�"NOR"\n", this_player());

	me->move(__DIR__"mishi1");
	return 1;
}


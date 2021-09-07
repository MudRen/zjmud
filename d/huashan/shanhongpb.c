//Room: shanhongpb.c ɽ���ٲ�
//Date: Oct. 2 1997 by Venus

#include <ansi.h>

//inherit BUILD_ROOM;
inherit ROOM;

string look_hongshui();

void create()
{
	set("short","ɽ���ٲ�");
	set("long",@LONG
������һ��Ͽ�ȣ�ÿ���꼾ɽ�鱬��ʱ���γ���һ��εΪ׳�۵�
�ٲ�����˵�������������������������ɾ��������������ġ�����
��ȥ�ȿգ�ֻʣ�¿��ȵ�ɽ�Ⱥͱ��ڵĺ�ˮ(hongshui)���������Ǹ�
���ӵĺ�ȥ����
LONG);
	set("outdoors", "huashan");
	set("max_room", 3);
	set("item_desc", ([
		"hongshui" : (: look_hongshui :),
	]));
	set("exits",([ /* sizeof() == 1 */
		"southwest"     : __DIR__"shaluo",
	]));
	setup();
}

void init()
{
	add_action("do_cross", "cross");
}

string look_hongshui()
{
	return @DESC
����һ�ɱ��ڲ�Ϣ�ĺ�ˮ��ˮ�������и������ڷ��⣬���㶨��
��ϸһ����������ֻ������ˮ�淴����չ���ˡ�����ٲ��ƺ�
���Դ�(cross)��ȥ��
DESC ;
}

int do_cross()
{
	object me;
	function f;
	object cloth;

	me = this_player();
	if (me->query_dex() / 2 + random(me->query_dex()) < 22)
	{
		message_vision("$N���������ڵ��ٲ���ͻȻһԾ����ͼ����"
			       "�ٲ����������ͨ��һ��ˤ����ˮ�С�\n", me);

		cloth = me->query_temp("armor/cloth");
		if (cloth && cloth->washed(120 + random(120)))
			tell_object(me, "�����ϵ�" + cloth->name() + "ʪ͸�ˣ�\n");
		return 1;
	}

	message_vision("$N���������ڵ��ٲ���ͻȻһԾ��������"
		       "�ٲ���\n", me);
	me->move(__DIR__"shandong");
	return 1;
}

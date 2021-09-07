//Room: guangchang.c �䵱�㳡
#include <ansi.h>

inherit ROOM;

void create()
{
      set("short", "�䵱�㳡");
      set("long",@LONG
����һ���ɴ�ʯ���̳ɵĹ㳡�����䵱����ѧϰ�书�ͻ����д�ĵص㡣
��Χ��������ͩ����һ������������ص���Ҷ��һ���������ĵ�ͯ���ڴ�ɨ��
�ϱ�������������
LONG);

      set("objects", ([
	   CLASS_D("wudang") +"/daotong": 2,
      ]));

      set("exits",([ /* sizeof() == 1 */
	  "northdown"  : __DIR__"zixiaogate",
	  "south"      : __DIR__"sanqingdian",
	  "northeast"   : __DIR__"tyroad1",
	  "east"       : __DIR__"shanlu2",
      ]));

	set("item_desc", ([
		"����ӡ��" : "һЩ��Ϊ������䵱���Ӿ����ڴ�ֱ�������ṦƮ��ɽ�£��ö���֮�˴��ȳ�һЩ�����Ľ�ӡ��\n"
		ZJOBACTS2"Ʈһ��:piao\n",
	]));
      set("outdoors", "wudang");
      setup();
}

void init()
{
	add_action("do_float", "piao");
}

int do_float()
{
	object me;

	me = this_player();

	if (me->query_skill("tiyunzong", 1) < 120 ||
	    me->query_skill("dodge", 1) < 120)
	{
		message_vision("$N��������ԭ�ر�����һ������������Ṧ���е���ˡ�\n", me);
		return 1;
	}

	if (me->query("neili") < 100)
	{
		tell_object(me, "�������������������Ϣһ����˵�ɡ�\n");
		return 1;
	}

	me->add("neili", -70);

	message_sort(HIC "$N" HIC"����һ������������Ц��ֻ������ƮȻ����̬�����ɣ��λ����Ƶ�����ɽȥ�ˣ�Ц����Ȼδ����"NOR"\n", me);
	tell_object(me, "Ƭ�̣����Ѿ��䵽��ɽ���¡�\n");
	me->move("/d/wudang/wdroad5");
	message("vision", "��Ȼһ��Ц��������ֻ��" + me->name() + "ƮȻ���£��������ɡ�\n", environment(me), ({ me }));
	return 1;
}

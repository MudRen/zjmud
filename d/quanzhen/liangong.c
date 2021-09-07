// liangong.c ������
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������ȫ��̵��������ķ��䡣����������״�������أ�ǰխ
�����Ϊ���Σ����߰�Բ������ȴ��������״��ԭ������ȫ���
���е������ң�ǰխ���ƣ����ʹָ����Բ�н������Ƿ��ڡ�����
�������ż��������õ�ľ�ˣ����ż���ɳ��(bag)��ֽ��(paper)��
LONG );

	set("exits", ([
		"south" : __DIR__"houtang2",
		"north" : __DIR__"chanfang2",
	]));
	set("item_desc", ([
		"paper" : "����һ������ţƤֽ�ᣬ����������ǽ�ϡ��������
�������Ʒ��ģ����(da paper)���Կ���\n",
		"bag"   : "����һ����ɳ�����������ǳ���ʵ��������������ָ��
�ģ�����Դ��(chi bag)����\n",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 4,
	]));
	set("for_family", "ȫ���");
	setup();
}

void init()
{
      add_action("do_strike", "da");
      add_action("do_finger", "chi");
}

int do_finger()
{
      object me;
      int qi_cost, c_skill;

      me = this_player();
      c_skill=me->query_skill("finger", 1);

      message_vision("$N��ָ�ݺݵص���ɳ��������ָ��΢΢��Щʹ��\n", me);
      qi_cost = 25;

      if (me->query("qi") > qi_cost)
      {
	   if (me->can_improve_skill("finger") && c_skill < 100)
		me->improve_skill("finger", 1 + random(me->query("str")));
	   me->receive_damage("qi", qi_cost);
      }
      return 1;
}

int do_strike()
{
      object me;
      int qi_cost, c_skill;

      me = this_player();
      c_skill = me->query_skill("strike", 1);

      message_vision("$N����һ���������ƻ���ţƤֽ�ᡣ\n", me);
      qi_cost = 25;

      if (me->query("qi") > qi_cost)
      {
	   if (me->can_improve_skill("strike") && c_skill < 100)
		me->improve_skill("strike", 1 + random(me->query("str")));
	   me->receive_damage("qi", qi_cost);
      }
      return 1;
}

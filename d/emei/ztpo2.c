//Room: ztpo2.c ������
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","������");
      set("long",@LONG
����ʯ��ϴ���֮�䣬��·������ʯջ���ݣ�ֱ�����죬ʯ�Ŵ�һǧ����
�༶�����ڶ���ɽ���Ͽ���������µ����������ϣ�ǰ������ӣ�һ����졣
���·�С������졹����ζ���Ҳ��˶��С������¡������������¶��㵽
ϴ��أ����¿ɴ�����ʯ��
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "eastdown"  : __DIR__"ztpo1",
	  "westup"    : __DIR__"xixiangchi",  
      ]));
      setup();
}

int valid_leave(object me, string dir)
{
	int c_skill;

	me = this_player();
	if (dir == "westup")
	{
		c_skill = me->query_skill("dodge", 1);
		if (me->query("qi") > 40)
		{
			me->receive_damage("qi", 20 + random(20));
			if (me->can_improve_skill("dodge") && c_skill < 100)
			   me->improve_skill("dodge", 1 + me->query_skill("dodge", 1) / 15);
			tell_object(me,"�����ϰ�ʮ���̣���Щ���ˡ�\n");
		} else
		{
			me->set("qi", 0);
			tell_object(me, "��̫���ˣ���Ҳ�߲����ˡ�\n");
			return -1;
		}
      }
      return 1;
}

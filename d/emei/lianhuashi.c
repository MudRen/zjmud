//Room: lianhuashi.c ����ʯ
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","����ʯ");
      set("long",@LONG
��������ʯ���˴���ʯ�����ݺᣬ��������������ܽ�أ��·��������
ϸ������������һ�֣��С������硹���ɴ�������ֱ��ϴ��أ�������ͨ����
������ͨ���϶���
LONG);
      set("objects", ([
	   CLASS_D("emei") + "/su" : 1,
	   CLASS_D("emei") + "/ling" : 1,
      ]));
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "southeast" : __DIR__"jldongkou",
	  "eastdown"  : __DIR__"huayanding",
	  "westup"    : __DIR__"ztpo1",  
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

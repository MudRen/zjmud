//Room: jsjdg1.c ��ʮ�ŵ���
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","��ʮ�ŵ���");
      set("long",@LONG
���������ġ���ʮ�ŵ��ա�����·����������ǧ�۰ٻء���˵��ȥ���и�
������ķ�ɮ���ˣ���һ������·�������������������ǵ�֪�˴��о�����û
�󣬱���Ҳ���˸�������Ĳ�ľ�����ԡ����ӡ���֮���ɴ˶�����ǧ���֣���
����϶���
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "westup"    : __DIR__"jsjdg2",
	  "northeast" : __DIR__"qianfoan",
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

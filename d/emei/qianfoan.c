//Room: qianfoan.c ǧ����
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","ǧ����");
      set("long",@LONG
�˴��Ǻ鴻ƺǧ���֡�ɽ��Сƺ�ӣ�������͵��ϣ��廷�뻤���������
��ᰣ�Ϫ���ᶣ��ƺ�Ϲ�ľ���裬ͤͤ��ǣ�ɽ����͸������Ʈ�Σ���Ϊ�ľ�
�������˴��������������������������ɣ���ɽ��������Ϊ������ν��ɽ�б�
���꣬�մ�ʪ���¡����������Ϊ��۵ġ��鴻���꡹���˴��������ģ�����
���죬����������;�����ǡ���ʮ�ŵ��ա������¾�������ջ����������
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "southwest" : __DIR__"jsjdg1",
	  "enter"     : __DIR__"qfadadian",
	  "north"     : __DIR__"heilong2",
      ]));
      setup();
}

int valid_leave(object me, string dir)
{
	int c_skill;

	me = this_player();
	if (dir == "southwest")
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

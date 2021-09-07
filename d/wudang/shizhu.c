//Room: shizhu.c ʯ��
//Date: Sep 22 1997

inherit ROOM;

void create()
{
      set("short","ʯ��");
      set("long",@LONG
�������ҹ�ǰ��һ��ʯ����������Σ����ͱ��Ϻ��������������졣����
��һ��¯���ڴ������Ϊ������ͷ�㡱������͵������Ը��ʯ��������������
���޷�����ǰ�а������ƣ�����������Ԩ����һʧ�㣬��ʬ���޴档
LONG);
      set("exits",([ /* sizeof() == 1 */
	  "northup"  : __DIR__"nanyanfeng",
	  "enter"    : __DIR__"nanyangong",
      ]));
      set("outdoors", "wudang");
      set("no_clean_up", 0);
      setup();
}

void init()
{
	add_action("do_mianbi", "face");
}


int do_mianbi(string arg)
{
	object ob;

	ob = this_player();
	if (! arg)
	{
		message_vision("$N�����ʯ��������˼���ã���"
			       "æһ����һ������\n",ob);
		return 1;
	}

	if ((int)ob->query_skill("literate", 1) < 100)
	{
		message_vision("$N�����ʯ������������ģ�û"
			       "һ������ʶ��\n",ob);
		return 1;
	}

	if ((int)ob->query_skill("taoism", 1) < 100)
	{
		message_vision("$N��ʯ����ÿһ���ֶ���ʶ����"
			       "�ǲ�֪��˵����ʲô��\n",ob);
		return 1;
	}

	if (arg == "taiji-jian" ||
	    arg == "taiji-quan" ||
	    arg == "tiyunzong")
	{
		if ((int)ob->query_skill(arg, 1) < 100)
		{
			message_vision("$N��" + to_chinese(arg) +
				       "��Ȼ̫�ͣ��޷�����ʯ�����ݡ�\n",ob);
			return 1;
		}

		if ((int)ob->query_skill(arg, 1) > 180)
		{
			message_vision("$N��" + to_chinese(arg) +
				       "�Ѿ�û��Ҫ��ʯ�������ˡ�\n", ob);
			return 1;
		}

		if (! ob->can_improve_skill(arg))
		{
			message_vision("$N��ʵս���鲻�㣬�޷�"
				       "����ʯ�����ݡ�\n", ob);
			return 1;
		}

		if (ob->query("jing") < 150)
		{
			message_vision("$N̫���ˣ������޷���"
				       "��ʯ�����ݡ�\n", ob);
			return 1;
		}

		message_vision("$N�����ʯ��������˼�����ã���" +
			       to_chinese(arg) + "��������\n", ob);
		ob->improve_skill(arg, 1 + random(ob->query("int")));
		ob->add("jing", -100 - random(50));
		return 1;
	}

	message_vision("$N�����ʯ��������˼�����ã���������\n", ob);
	return 1;
}

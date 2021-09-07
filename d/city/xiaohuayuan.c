// xiaohuayuan.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","С��԰");
	set("long", @LONG
������һ��С��԰������ķ�������ʮ���ʺϸ��ֻ����������ر�
��һЩʮ������Ļ��֣�����Ҳ�����������ߵĻ��������򵽻������ӣ�
������������ֻ����Ա���һ��С�ţ���������һЩ��̸����������
LONG
	);

	set("exits", ([ 
		"west"  : __DIR__"huafang",
		"east" : __DIR__"liaotian",
	]));

	set("action_list", ([ 
		"�ֻ�"  : "zhonghua",
		"����" : "jiaoshui",
		"����" : "peiyu",
	]));

	set("no_fight", 1);
	setup();
}

void init()
{
	add_action("do_jiaoshui", "jiaoshui");
	add_action("do_peiyu", "peiyu");
}

int do_peiyu()
{
	object ob,me;
	me = this_player();

	if (! me->query_temp("zhonghua"))
	{
		tell_object(me, HIR "�����Ӷ�û�У������ֻ���"NOR"\n"); 
		return 1;
	}

	if (me->query_temp("jiaoshui") == 1)
	{
		tell_object(me,HIR "���Ѿ��������������������ڿ��Խ�ˮ(jiaoshui)��"NOR"\n");
		return 1;
	}

	if (me->query("combat_exp") > 150000 || me->query("combat_exp") < 10000)
	{
		tell_object(me,HIR "�������ݴ�Ų��ʺ���С��԰�ֻ��ɣ�"NOR"\n");
		return 1;
	}

	if (me->query("jing") < 70)
	{
		message_vision(HIR "$Nһ���������������ӣ���ô���ֻ��أ�"NOR"\n",me);
		return 1;
	}

	message_vision("$N��������Χ�úõ�������һ�£�ʹ���������ʺϻ���������\n", me); 
	me->set_temp("peiyu",1);
	me->set_temp("jiaoshui",1);
	me->start_busy(1 + random(3));
	return 1;
}

int do_jiaoshui()
{
	object me,ob;

	me = this_player();

	if (me->query("jing") < 70)
	{
		tell_object(me,HIR "����ɫ���ã�������Ϣ��Ϣ�ɡ�"NOR"\n"); 
		return 1;
	}

	if (me->is_busy())
	{
		tell_object(me, HIR "����æ���أ����ż���"NOR"\n");
		return 1;
	}

	if (! me->query_temp("peiyu") == 1)
	{
		tell_object(me,HIR "������������û�¸ɽ�ʲôˮ����"NOR"\n");
		return 1;
	}

	if (me->query_temp("peiyu") == 2)
	{
		if (random(14) == 1)
		{
			switch (random(5))
			{
				case 1 : ob = new("/d/changan/npc/obj/hmeigui"); break;
				case 2 : ob = new("/d/changan/npc/obj/zi-luolan"); break;
				case 3 : ob = new("/d/changan/npc/obj/bai-chahua"); break;
				case 4 : ob = new("/d/changan/npc/obj/huang-meigui"); break;
				case 0 : ob = new("/d/changan/npc/obj/lan-tiane"); break;
			}

			if (random(15) == 1)
			{
				if (random(10000) == 1)
				{
					ob = new("/d/shenlong/obj/hua4");
					CHANNEL_D->do_channel(this_object(), "rumor",me->query("name") + "��С��԰�ֳ�һ���������");
					message_vision(HIR "$N" HIR "�õ����������"NOR"\n",me);
					ob->move(me, 1);
					me->delete_temp("jiaoshui");
					me->delete_temp("zhonghua");
					me->delete_temp("peiyu");
					me->add("combat_exp", 500);
					me->improve_potential(100 + random(100));
					return 1;
				}

				ob = new("/d/shenlong/obj/hua2");
				me->add("combat_exp", 20 + random(10));
				me->improve_potential(20 + random(10));
				CHANNEL_D->do_channel(this_object(), "rumor",me->query("name") + "��С��԰�ֳ�һ����������");
				return 1;
			}

			message_vision(HIC "$N" HIC "ʮ��С�ĵĸ�С���ｽ��һЩˮ��ͻȻ" + ob->query("long") + "�ӿ���ð�˳�����"NOR"\n",me);   
			message_vision(HIR "$N" HIR "����ժ���������������"NOR"\n",me);
			ob->move(me, 1);
			me->delete_temp("jiaoshui"); 
			me->delete_temp("peiyu"); 
			me->delete_temp("zhonghua"); 
			me->add("combat_exp", 20 + random(10)); 
			me->improve_potential(10 + random(10));
			return 1; 
		}

		message_vision(HIR "$N" HIR "���ֱ��ŵ�����ˮ����С���ｽˮ�����ˮ����̫��ѻ������ˡ�\n",me); 
		me->delete_temp("jiaoshui"); 
		me->delete_temp("zhonghua"); 
		me->delete_temp("peiyu"); 
		me->add("jing", -50);
		me->add("combat_exp", 3);
		me->improve_potential(2); 
		return 1; 
	}

	if (me->query_temp("jiaoshui") == 1)
	{
		message_vision("$N����ˮ����С�ӽ���һЩˮ��\n",me); 
		me->add("jing", -70); 
		me->set_temp("peiyu", 2); 
		me->start_busy(1 + random(2)); 
		return 1;
	}
}

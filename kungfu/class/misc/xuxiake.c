// xuxiake.c ��ϼ��

#include <ansi.h>

inherit NPC;

mixed ask_map();

void create()
{
	set_name("��ϼ��", ({ "xu xiake", "xu" }));

	set("gender", "����");
	set("age", 45);
	set("long",
		"�������߱����£���ʶ��������������ۣ���ɽ������Ī������ָ�ơ�\n");

	set("attitude", "friendly");
	set("inquiry", ([
		"��ͼ" : (: ask_map :),
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

mixed ask_map()
{
	object me, ob;
	mapping map;
	string *ks;
	string msg;
	string str;
	int n;

	ob = this_object();
	me = this_player();
	if (! me->query("out_family"))
	{
		message_vision("$N΢΢һЦ����$n�����������ϴ��˵�ͼ��ô����\n",ob, me);
		return 1;
	}

	if (me->query("map_all"))
	{
		message_vision("$NЦ������" + RANK_D->query_respect(ob) + "����ĵ�ͼ���Ѿ���¼��ȫ���ˣ����絽�������߰ɡ���\n",ob, me);
		return 1;
	}

	if (! mapp(map = me->query("map")))
		return "Ŷ�����Ȿ��ͼ�ỹȫ�ǰ�ֽ�أ�";

	// �鿴��Щ�ط�û�л���
	ks = (string *) MAP_D->query_all_map_zone() - keys(map);
	if (sizeof(ks) < 3)
	{
		n = 0;
		foreach (str in keys(map))
			n += sizeof(map[str]);
		if (n < 600)
		{
			message_sort("$N�ӹ�$n�ĵ�ͼ�ᣬ��ϸ����һ�����̾������"
				     "�ҿ�������Ƶĵ�ͼ���ˣ���¼�ĵص㵹����ȫ"
				     "�ģ���ϧ�ܶ�ط����ز��飬Ŀǰֻ��¼��"+n+"���ط���������¼600���ص���������Ұɡ���\n", ob, me);
			return 1;
		}

		message_sort("$N�ӹ�$n�ĵ�ͼ�ᣬ��ϸ����һ�������˼���ã��ַ���"
			     "��һ�󣬲��ɵ�ϲ��ü�ң���$n�޵�����ʵ�ڲ����뵽��"
			     "���ϻ�����������һ���߱���ɽ�󴨣��ѵã��ѵã��ţ�"
			     "�ҿ���ĵ�ͼ���л�������ȱ©����͸��㲹ȫ�ɣ��պ�"
			     "������õ��ϡ���˵�꣬$N��������ʣ���$n�ĵ�ͼ��"
			     "�ϲ��˼��ʣ�������$n��\n", ob, me);
		me->delete("map");
		me->set("map_all", 1);
		CHANNEL_D->do_channel(this_object(), "rumor",
				      "��˵" + me->name(1) + "(" + me->query("id") +
				      ")����ϼ���̵ֽ���ɽ��֪ʶ������˵�ͼȫ����");
            me->add("combat_exp",50000);
		me->add("potential", 5000);
		me->add("score", 1000);
		tell_object(me, HIG "����ϸ�����˵�ͼȫ����˼����ã��ջ����࣬��"
				"����ʮ��㾭�顢һ���Ǳ�ܺ���ǧ�㽭��������"NOR"\n");
		return 1;
	}

	if (sizeof(ks) > 3) ks = ks[0..2];
	ks = map_array(ks, (: MAP_D->query_map_short($1) :));
	msg = "$N�ӹ�$n�ĵ�ͼ�ᣬ��ϸ����һ�������ü���������ҿ�����"
	      "����������Ƶĵ�ͼ���൱��ȫ�أ�����" +
	      implode(ks, "��") + "��û����¼���ڡ���\n";
	message_sort(msg, ob, me);
	return 1;
}

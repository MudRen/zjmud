// japanese.c �ձ�����

inherit CHALLENGER;

void create()
{
	object ob;

	set_name("�ձ�����", ({ "japanese" }));
	set("long", "�ձ����ӡ�\n");
	set("gender", "����");
	set("age", 20);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);

	// the follow 5 setting has no use
	set("max_qi", 10000);
	set("max_jing", 10000);
	set("neili", 10000);
	set("max_neili", 10000);
	set("jiali", 100);
	set("shen", -1000);

	set("combat_exp", 3000000);
	set("scale", 100);

	set_skill("force", 200);
	set_skill("fushang-neigong", 200);
	set_skill("dodge", 200);
	set_skill("renshu", 200);
	set_skill("parry", 200);
	set_skill("dongyang-dao", 200);
	set_skill("blade", 200);

	map_skill("blade", "dongyang-dao");
	map_skill("force", "fushang-neigong");
	map_skill("dodge", "renshu");
	map_skill("parry", "dongyang-dao");

	set("rank_info/rude", "����");

	set("die_give", ([
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
	]));

	set("die_give2", ([
		"/clone/vip/dan_jiuzhuan" : 2,
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: perform_action, "blade.luan" :),
		(: perform_action, "blade.zhan" :),
	}));

	setup();

	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/jpn-dao")->wield();
}

string challenge()
{
	set("opinion/msg", ({
		(random(2) ? "�������Զ����ɣ����˵����Ķ��󵶷�������졣"
			   : "�����ɣԶ�ڶ���֮�⣬�������ʿ�ó�ʹ��խ�г�����"),
		(random(2) ? "�ǰ�����������Ҳ�ǹ��صúܡ�"
			   : "û�����������������أ����������������������"),
		(random(2) ? "�ߣ���������������ţ�ʵΪϰ���ߴ�ɣ�"
			   : "���˿�ν��Ŀ��⣬��֪������һ˿Ҳ�����ã�"),
	}));

	command(random(2) ? "haha" : "heng");
	switch (random(3))
	{
	case 0:
		return "�ң������ʿ" + name() + "������������ԭ"
			"������ս��˭�ҳ���ӭս��";

	case 1:
		return "�Ҿ��Ƕ����ɣ����" + name() + "��������"
			"ԭ��û�������ҵĶ��֣�";

	default:
		return "��" + name() + "��������ʿ����������ս"
			"�����ֵľ͸��ҹ�������";
	}
}

void unconcious()
{
	command("chat �˸�ѽ·��");
	die();
}

void competition_with(object ob)
{
	command("say �˸�ѽ·������ȥ�ɣ�\n");
	::competition_with(ob);
	kill_ob(ob);
}

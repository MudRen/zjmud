// european.c ������

#include <ansi.h>

inherit CHALLENGER;

void create()
{
	set_name("������", ({ "european" }));
	set("long", "һ�������ˡ�\n");
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
	set_skill("xiyang-neigong", 200);
	set_skill("dodge", 200);
	set_skill("xiyang-boji", 200);
	set_skill("parry", 200);
	set_skill("xiyang-jian", 200);
	set_skill("sword", 200);

	map_skill("sword", "xiyang-jian");
	map_skill("force", "xiyang-neigong");
	map_skill("dodge", "xiyang-boji");
	map_skill("parry", "xiyang-jian");

	set("rank_info/rude", "��ë��");

	set("die_give", ([
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
		"/clone/vip/putao" : 2,
	]));

	set("die_give2", ([
		"/clone/vip/dan_jiuzhuan" : 5,
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: perform_action, "sword.ci" :),
		(: perform_action, "sword.lian" :),
	}));

	setup();

	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/xiyang-sword")->wield();
}

string challenge()
{
	set("opinion/msg", ({
		(random(2) ? "�������Ծ�˵�Ǳȶ���˹��Ī˹�ƻ�ҪңԶ��������"
			   : "����������ʿ�������������˴�һ����"),
		(random(2) ? "�ǰ���ңԶ�ĵط����似Ҳ����Ϊ���ء�"
			   : "�ţ����������˴̻���������������������"),
		(random(2) ? "�����ңԶ�ĵط�������Ҳ���ǹ���Ϊ�����ˣ�"
			   : "��������Ȼע��ʵսЧ����������Ȼ�㲻�����ϳ˽�����"),
	}));

	command(random(2) ? "haha" : "killair");
	switch (random(2))
	{
	case 0:
		return "������" + query("nation") + "����˵������ԭ"
			"�����������ص�ǰ���д��д裡";

	default:
		return "����" + query("nation") + "��" + name() + "��������"
		       "ԭ��û����Ը����ұ���һ�����գ�";
	}
}

void competition_with(object ob)
{
	command("say �ðɣ����Ǿͷָ��ߵͿ�����\n");
	::competition_with(ob);
}

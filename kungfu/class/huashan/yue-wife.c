// yue-wife.c    changed by cocacola on 2.19.1997 Just for adding Chushi
// ������

inherit NPC;
inherit F_MASTER;

#include "qizong.h"

void create()
{
	set_name("������", ({ "yue wife", "ning", "ning zhongze" }) );
	set("nickname", "��Ů��");
	set("gender", "Ů��");
	set("class", "swordsman");
	set("age", 50);
	set("long", "������ԭ����������������"
		    "������Ⱥ��ʦ�ã�Ҳ���������ӡ�\n");
	set("attitude", "peaceful");
	set("shen_type", 1);

	set("str", 24);
	set("int", 25);
	set("con", 23);
	set("dex", 22);

	set("max_qi", 3000);
	set("max_jing",1500);
	set("neili", 3700);
	set("max_neili", 3700);
	set("jiali", 30);
	set("combat_exp", 720000);

	set("apprentice_available", 3);

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :)
	}) );

	set_skill("unarmed", 110);
	set_skill("sword", 140);
	set_skill("force", 130);
	set_skill("parry", 140);
	set_skill("dodge", 130);
	set_skill("literate", 100);

	set_skill("huashan-sword", 140);
	set_skill("yunu-sword", 140);
	set_skill("huashan-xinfa", 130);
	set_skill("huashan-quanfa", 110);
	set_skill("feiyan-huixiang", 130);

	map_skill("sword", "yunu-sword");
	map_skill("parry", "yunu-sword");
	map_skill("force", "huashan-xinfa");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("dodge", "feiyan-huixiang");

	set("apply/damage", 120);
	set("apply/armor", 100);
	set("apply/defense", 50);

	create_family("��ɽ��", 13, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
	if( query("apprentice_available") ) {
		if( find_call_out("do_recruit") != -1 )
			command("say ������һ��һ������");
		else
			call_out("do_recruit", 2, ob);
	} else {
		command("say �������Ӵ��");
	}
}

void do_recruit(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((string)ob->query("gender") != "Ů��")
	{
		command("say ��λ"+RANK_D->query_respect(ob) +
			"�㻹�����ҷ��ȥ��.");
		return;
	}

	command("say ΢Ц�����ã��ã�ֻҪ������ѧ�����ձ��гɾ͡�");
	command("recruit " + ob->query("id") );
}

int recruit_apprentice(object ob)
{
	if (::recruit_apprentice(ob))
		ob->set("class", "huashan");
	add("apprentice_availavble", -1);
}

void reset()
{
	set("apprentice_available", 3);
}


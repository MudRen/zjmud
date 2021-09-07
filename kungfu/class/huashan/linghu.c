// linghu.c �����

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "qizong.h"

mixed ask_me();

void create()
{
	set_name("�����", ({ "linghu chong", "linghu", "chong" }));
	set("nickname", "��ʦ��");
	set("long", "�����Ľ��ݣ�����Ũü���ۣ������Ѱ�����ͬ���������ϴ�\n"
		    "�ǻ�ɽ������һ���еĶ�����֡�\n");
	set("gender", "����");
	set("age", 28);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 30);
	set("int", 40);
	set("con", 30);
	set("dex", 30);
	
	set("qi", 4800);
	set("max_qi", 4800);
	set("jing", 2400);
	set("max_jing", 2400);
	set("neili", 5700);
	set("max_neili", 5700);
	set("jiali", 60);

	set("combat_exp", 2200000);
	set("score", 150000);

	set_skill("blade", 120);
	set_skill("cuff", 120);
	set_skill("feiyan-huixiang", 200);
	set_skill("strike", 120);
	set_skill("huashan-zhangfa",120);
	set_skill("unarmed",120);
	set_skill("huashan-quanfa",120);
	set_skill("force", 220);
	set_skill("yijinjing", 220);
	set_skill("dodge", 200);
	set_skill("parry", 220);
	set_skill("sword", 240);
	set_skill("huashan-sword", 240);
	set_skill("lonely-sword", 240);
	set_skill("literate", 40);
	set_skill("tanqin-jifa", 250);
	set_skill("xiaoao-jianghu", 250);
	set_skill("qingxin-pushan", 250);

	map_skill("force", "yijinjing");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("strike", "huashan-zhangfa");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("parry", "lonely-sword");
	map_skill("sword", "lonely-sword");
	map_skill("tanqin-jifa", "xiaoao-jianghu");

	create_family("��ɽ��", 14, "����");

	set("inquiry", ([
		"������" : "�����Ѿ��ܾ�û�м��������˼��ˡ���������",
		"��ӯӯ" : "��Ҫ��ʲô�������鷳��",
		"����������" : "�����ӨӨ�̸��ҵ�...",
		"Ц������"   : "���������Ϻ�������ʦ����������...����",
		"����"       : (: ask_me :),
     	]));

	set("no_teach", ([
		"yijinjing" : "���������ش����ɷ�����ʦ���ڣ��Ҳ������Խ��㡣",
		"lonely-sword" : "�����������ҾŽ���ʱ�����������Բ���˽"
				 "�Դ��ڣ��㻹��ѧϰ�����书�ɣ�",
	]));

	set("music_book", 1);
	setup();	 	
	carry_object("/d/heimuya/npc/obj/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/heimuya/npc/obj/card2");
}

int recognize_apprentice(object me, string skill)
{
	if (skill != "tanqin-jifa" &&
	    skill != "xiaoao-jianghu" &&
	    skill != "qingxin-pushan")
	{
		command("say �Բ���...�Ҳ��ܴ�������Щ����Ҫ����ѧ����ټ�������ࡣ");
		return -1;
	}

	if (me->query_temp("can_learn/linghu/" + skill))
		return 1;

	me->set_temp("can_learn/linghu/" + skill, 1);
	command("say �ðɣ����Ȼ��" + to_chinese(skill) +
		"����Ȥ���Ҿͽ���һ�㡣");

	return 1;
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query("combat_exp") < 1000000)
	{
		command("say ���ʵս���鲻�У��Ҳ�������Ϊͽ��");
		return;
	}

	if (ob->query_int() < 28)
	{
		command("say ����������̫�ѧ���û�ɽ�ɵĹ���");
		return;
	}

	if (ob->query_skill("sword", 1) < 120)
	{
		command("say ��ɽ���������Խ�Ϊ��������Ļ���"
			"������û��ѧ�ã��ҿ����˰ɡ�");
		return;
	}

	if( ob->query_skill("force", 1) < 120 )
	{
		command("say ��Ȼ��������������������������ʵ"
			"սЧ��Ҳ����ã����ȴ���ڹ�������");
		return;
	}

       	command("nod");
	command("say �ðɣ�����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
	return;
}

mixed ask_me()
{
	object me;
	object ob;

	me = this_player();
	if (query("music_book") < 1)
		return "�ҵ������Ѿ����ȥ�ˡ�\n";

	ob = new("/clone/book/qin");
	ob->move(me, 1);
	message_vision("$n�����׸���$N����������ȥ�ú�ѧϰ�ɡ�\n",
		       me, this_object());
	set("music_book", 0);
	return 1;
}

void reset()
{
	set("music_book", 1);
}


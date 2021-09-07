// xiaoyaozi.c ��ң��
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include "xiaoyao.h"

void create()
{
	set_name("��ң��", ({ "xiaoyao zi", "xiaoyao","zi" }));
	set("title", "��ң�ɿ�ɽ��ʦ");
	set("long", @LONG
��ǰ������ü�԰ף��������ж��ϡ�Ȼ���ƺ���Ⱦ�ؼ����ж����㡣��Ȼ
��ˣ���ü����Ȼ���ó����˵����Ȼ��һλ�������ε������ӡ��벻��
�������䵽����ز��������������ϡ�
LONG );
	set("gender", "����");
	set("age", 75);
	set("class", "scholar");
	set("attitude", "friendly");
	set("shen_type", 1);

	set("str", 36);
	set("int", 41);
	set("con", 37);
	set("dex", 38);
	
	set("max_qi", 6200);
	set("max_jing", 3100);
	set("neili", 7700);
	set("max_neili", 7700);
	set("jiali", 100);
	set("combat_exp", 2700000);

	set_skill("force", 270);
	set_skill("xiaoyao-xinfa", 270);
	set_skill("beiming-shengong", 270);
	set_skill("xiaowuxiang", 270);
	set_skill("dodge", 270);
	set_skill("lingbo-weibu", 270);
	set_skill("feiyan-zoubi", 270);
	set_skill("liuyang-zhang", 240);
	set_skill("parry", 270);
	set_skill("blade", 240);
	set_skill("ruyi-dao", 240);
	set_skill("zhemei-shou", 240);
	set_skill("hand", 240);
	set_skill("strike", 240);
	set_skill("literate", 200);
	set_skill("medical", 290);
	set_skill("xiaoyao-qixue", 290);

	map_skill("force", "beiming-shengong");
	map_skill("dodge", "lingbo-weibu");
	map_skill("hand", "zhemei-shou");
	map_skill("strike", "liuyang-zhang");
	map_skill("parry", "ruyi-dao");
	map_skill("blade", "ruyi-dao");

	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");

	create_family("��ң��", 1, "��ɽ��ʦ");
	set("class", "taoist");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "blade.ruyi" :),
		(: perform_action, "hand.jiubu" :),
		(: perform_action, "strike.jiutian" :),
		(: perform_action, "dodge.lingbo" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object("/clone/weapon/blade")->wield();
}

void attempt_apprentice(object ob)
{
	if (ob->query_temp("pass_zhenlong"))
	{
		int btimes;
		ob->delete_temp("pass_zhenlong");
		if (ob->query("betrayer/times"))
		{
			command("sigh");
			command("say ���������磬��������Ե�ˣ�������������ʦ��ȴ�������㡣");
			return;
		}

		command("haha");
		command("say ���������磬��������Ե�ˣ���һ��Ҫ����Ϊͽ��");
		btimes = ob->query("betrayer/times");
		command("recruit " + ob->query("id"));
		ob->set("betryer/times", btimes);

		if (ob->query("max_neili") < 500)
		{
			command("say ����������̫��... ���Ҵ������㣡");
			ob->set("max_neili", 500 + random(100));
			if (ob->query_skill("force", 1) < 50)
				ob->set_skill("force", 50 + random(10));

			if (ob->query_skill("beiming-shengong", 1) < 50)
				ob->set_skill("beiming-shengong", 50 + random(10));

			message_vision("$N�����İ���$n������ϣ�˫��΢�������Ʋ�ס�Ĳ������������£����������ã��ã�\n",
				       this_object(), ob);
		}

		return;
	}

	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_skill("xiaoyao-xinfa", 1) < 120 &&
	    (int)ob->query_skill("beiming-shengong", 1) < 120) {
		command("say ����ң�ɵı����ڹ����㶼û��ѧ��������̸ʲô��"); 
		return;
	}

	if ((int)ob->query_skill("force", 1) < 120) {
		command("say ����ң�ɵĵ��书���������ڹ������Ȱ��ڹ�������á�"); 
		return;
	}

	if ((int)ob->query_skill("dodge", 1) < 120) {
		command("say ��ң��ң�����Ṧ������ô���̸��ң��"); 
		return;
	}

	if (ob->query_int() < 38) {
		command("say ����ң�����ľ����򣬵���" + RANK_D->query_respect(ob) + "�������ƺ����д���߰���");
		return;
	}

	if (ob->query("combat_exp") < 250000)
	{
		command("say ��ľ���Ҳ߯���˵㣬�úö���������˵�ɡ�");
		return;
	}

	command("smile");
	command("chat �벻���������Ͼ�Ȼ�����˿��Լ̳�����ң�ɵ��²���");
	command("recruit " + ob->query("id"));
	ob->set("title", HIC "��ң����" NOR);
}

void unconcious()
{
	die();
}

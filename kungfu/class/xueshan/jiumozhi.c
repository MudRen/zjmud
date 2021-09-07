// /kungfu/class/xueshan/jiumozhi.c �Ħ��
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "xueshan.h"

mixed ask_me();

void create()
{
	set_name("�Ħ��", ({ "jiumo zhi", "zhi" ,"ming wang"}));
	set("nickname", HIG "��������" NOR);
	set("long",@LONG
������ѩɽ�µ����ţ��˳ƴ����������Ħ�ǡ����Է��о�����о���
��һ��������ģ�ͷ��ɮñ��
LONG
	);
	set("title","ѩɽ������");
	set("gender", "����");
	set("age", 60);
	set("attitude", "friendly");
	set("shen_type", -1);

	set("str", 32);
	set("int", 40);
	set("con", 31);
	set("dex", 31);

	set("max_qi", 5800);
	set("max_jing", 2900);
	set("neili", 7100);
	set("max_neili", 7100);
	set("jiali", 100);
	set("combat_exp", 2500000);

	set_skill("force", 270);
	set_skill("xiaowuxiang", 270);
	set_skill("mizong-neigong", 270);
	set_skill("dodge", 240);
	set_skill("shenkong-xing", 240);
	set_skill("parry", 270);
	set_skill("sword", 220);
	set_skill("mingwang-jian", 220);
	set_skill("lamaism", 250);
	set_skill("literate", 220);
	set_skill("strike", 270 );
	set_skill("huoyan-dao", 270);
	set_skill("cuff", 260);
	set_skill("yujiamu-quan", 260);
	set_skill("hand", 270);
	set_skill("dashou-yin", 270);
	set_skill("sanscrit", 280);

	map_skill("force", "xiaowuxiang");
	map_skill("dodge", "shenkong-xing");
	map_skill("parry", "mingwang-jian");
	map_skill("sword", "mingwang-jian");
	map_skill("strike","huoyan-dao");
	map_skill("cuff", "yujiamu-quan");

	prepare_skill("strike", "huoyan-dao");
	prepare_skill("hand", "dashou-yin");

	create_family("ѩɽ��", 1, "����");
	set("class", "bonze");

	set("inquiry", ([
		"����" : (: ask_me :),
		"����" : (: ask_me :),
		"����" : (: ask_me :),
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.bei" :),
		(: perform_action, "hand.jingang" :),
		(: perform_action, "strike.fen" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/xueshan/obj/r-jiasha")->wear();
	carry_object("/d/xueshan/obj/sengmao")->wear();

	add_money("silver",50);
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/huoyan-dao/fen"))
		return "�������Ѿ�ѧ���ˣ�ʣ�µľ�Ҫ�����Լ�����ϰ�ˡ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return "��Ȼ��������ѩɽ��֮�ˣ���ʲô��̸�ġ�";

	if (me->query_skill("huoyan-dao", 1) < 120)
		return "��Ļ��浶����Ϊ��������������������˵�ɣ�";

	message_vision(HIC "$n" HIC "����һ������·���ε���Ϯ����$N"
		       HIC "��$N" HIC "��æ���ָ񵲣���������$n"
		       HIC "���������ÿ�ν�ǰ������"NOR"\n",
		       me, this_object());
	command("simle");
	tell_object(me, HIG "��ͨ���˷���İ��"NOR"\n");
	if (me->can_improve_skill("parry"))
		me->improve_skill("parry", 90000);
	me->set("can_perform/huoyan-dao/fen", 1);
	return 1;
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;
 
	if ((string)ob->query("gender") != "����")
	{
		command("say ��ϰ�����ڹ���Ҫ����֮�塣");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"������ذɣ�");
		return;
	}

	if ((string)ob->query("class") != "bonze")
	{
		command("say �ҷ��ŵ����������ࡣ");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"������ذɣ�");
		return;
	}

	if ((string)ob->query("family/family_name") != "ѩɽ��")
	{
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�ȷǱ��µ��ӣ�������ذɣ�");
		return;
	}

	if ((int)ob->query_skill("lamaism", 1) < 150) {
		command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
		return;
	}

	command("recruit " + ob->query("id"));
	ob->set("title", HIY "����" NOR);
}

void unconcious()
{
	die();
}

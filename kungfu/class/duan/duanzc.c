// duanzc.c ������

#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_jue();

void create()
{
	set_name("������", ({ "duan zhengchun", "duan" }));
	set("title",  "����������" );
	set("long", "�����Ǵ�������������������̫�ܣ��������İ���ʥ�֡�\n");
	set("gender", "����");
	set("age", 45);
	set("class", "royal");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 28);
	set("int", 30);
	set("con", 31);
	set("dex", 30);
	
	set("max_qi", 4200);
	set("max_jing", 2000);
	set("neili", 5400);
	set("max_neili", 5400);
	set("jiali", 70);
	set("combat_exp", 1400000);
	set("score", 45000);

	set_skill("force", 180);
	set_skill("dodge", 170);
	set_skill("parry", 180);
	set_skill("cuff", 150);
	set_skill("strike", 140);
	set_skill("sword", 160);
	set_skill("staff", 160);
	set_skill("finger", 180);
	set_skill("duanshi-xinfa", 180);
	set_skill("tiannan-step", 170);
	set_skill("jinyu-quan", 150);
	set_skill("wuluo-zhang", 140);
	set_skill("duanjia-sword", 160);
	set_skill("sun-finger", 180);
	set_skill("literate", 160);

	map_skill("force", "duanshi-xinfa");
	map_skill("dodge", "tiannan-step");
	map_skill("finger", "sun-finger");
	map_skill("cuff", "jinyu-quan");
	map_skill("strike", "wuluo-zhang");
	map_skill("parry", "sun-finger");
	map_skill("sword", "duanjia-sword");
	map_skill("staff", "duanjia-sword");
	prepare_skill("cuff", "jinyu-quan");
	prepare_skill("strike", "wuluo-zhang");

	set("inquiry", ([
		"�����" : (: ask_jue :),
		"�μ������" : (: ask_jue :),
		     ]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "finger.qiankun" :),
		(: perform_action, "finger.dian" :),
		(: perform_action, "sword.jing" :),
		(: perform_action, "sword.jue" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 50);

	create_family("���ϻ���", 15, "����");
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	command("say �ã��ú�ѧϰ���Ƕμҵ��似��");
	command("recruit " + ob->query("id"));
	return;
}

mixed ask_jue()
{
	object me;

	me = this_player();
	if (me->query("can_perform/duanjia-sword/jue"))
		return "�㲻���Ѿ�ѧ���������ô����Ҫ���������ҿɴ����㡣";

	if (me->query("family/family_name") != query("family/family_name"))
		return "���ֲ������ǶμҵĴ��ˣ�����ʲô��˼��";

	if (me->query("shen") < 0)
		return "���˰ɣ��������ֻ������ȥ����";

	message_vision(CYN "$n" CYN "��$N" CYN "��Ц����������"
		       "�书ѧ��Ҳ���ã��㻹�����ʻ��ְɣ�"NOR"\n",
		       me, this_object());

	return 1;
}

void unconcious()
{
	die();
}

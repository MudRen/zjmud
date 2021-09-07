// duanzm.c ������

#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_jue();

void create()
{
	set_name("������", ({ "duan zhengming", "duan" }));
	set("title",  "�������" );
	set("long", "�����Ǵ�����Ĺ������̳����������Ļ�ҵ��\n");
	set("gender", "����");
	set("age", 49);
	set("class", "royal");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 32);
	set("int", 35);
	set("con", 32);
	set("dex", 29);

	set("max_qi", 5800);
	set("max_jing", 3000);
	set("neili", 6500);
	set("max_neili", 6500);
	set("jiali", 100);
	set("combat_exp", 2250000);
	set("score", 60000);

	set_skill("force", 250);
	set_skill("dodge", 240);
	set_skill("parry", 250);
	set_skill("cuff", 240);
	set_skill("sword", 240);
	set_skill("staff", 240);
	set_skill("finger", 250);
	set_skill("duanshi-xinfa", 250);
	set_skill("tiannan-step", 240);
	set_skill("jinyu-quan", 240);
	set_skill("duanjia-sword", 240);
	set_skill("sun-finger", 250);
	set_skill("literate", 180);

	map_skill("force", "duanshi-xinfa");
	map_skill("dodge", "tiannan-step");
	map_skill("finger", "sun-finger");
	map_skill("cuff", "jinyu-quan");
	map_skill("strike", "wuluo-zhang");
	map_skill("parry", "sun-finger");
	map_skill("sword", "duanjia-sword");
	map_skill("staff", "duanjia-sword");
	prepare_skill("finger", "sun-finger");

	set("inquiry", ([
		"����" : (: ask_jue :),
		"����" : (: ask_jue :),
		"�����" : (: ask_jue :),
		"�μ������" : (: ask_jue :),
		"���������" : (: ask_jue :),
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

	if (ob->query_skill("duanshi-xinfa", 1) < 100)
	{
		command("say ���Ⱥú�ѧϰ���Ƕμҵ��ķ����Ժ�����ָ���㡣");
		return;
	}

	if (ob->query("combat_exp") < 200000)
	{
		command("say ������ʵս����̫���ˣ��ú��ڽ�"
			"������������Ҫʧ�����Ƕ��ϵ����ӡ�\n");
		return;
	}

	command("say �ã����������ˣ������似��Ȼ��Ҫ��Ҳ��"
		"Ҫ���Ƕ����ι�����");
	command("recruit " + ob->query("id"));
	return;
}

mixed ask_jue()
{
	object me;

	me = this_player();
	if (me->query("can_perform/duanjia-sword/jue"))
		return "�㲻���Ѿ�ѧ���������ô������ʲô����ô��";

	if (me->query("family/family_name") != query("family/family_name"))
		return "���ֲ������ǶμҵĴ��ˣ�����ʲô��˼��";

	if (me->query("shen") < 0)
		return "���˰ɣ��������ֻ������ȥ����";

	if (me->query_skill("duanjia-sword", 1) < 100)
		return "��Ķμҽ��������У�������˵�ɣ�";

	message_vision(HIC "$n" HIC "���ͷ����Ȼ����ǰ������"
		       "��Ϊ���������У���ʽ�����ޱȣ�$N"
		       HIC "���һ����ֻ�ܺ��ˡ�"NOR"\n",
		       me, this_object());
	command("smile");
	command("say �㿴�����ô���Ժ��Ҫ�������壬ĪҪ������Ϊ��");
	tell_object(me, HIG "��ѧ���˶μ��������"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 90000);
	me->set("can_perform/duanjia-sword/jue", 1);
	return 1;
}

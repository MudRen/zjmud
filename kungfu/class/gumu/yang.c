// yang.c ���

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "gumu.h"

string ask_yunv();
int not_to_learn_ss(object ob);

void create()
{
	set_name("���", ({"yang guo", "yang"}));
	set("gender", "����");
	set("age", 26);
	set("long", @LONG
������ȥüĿ֮����һ������֮����Ȼ������ԼԼȴ���˸е�һ����֮�飬
����յ����ģ���Ȼ���ǲм���
LONG );
	set("attitude", "friendly");

	set("str", 35);
	set("int", 36);
	set("con", 34);
	set("dex", 32);

	set("qi", 5800);
	set("max_qi", 5800);
	set("jing", 2900);
	set("max_jing", 2900);
	set("neili", 8500);
	set("max_neili", 8500);
	set("jiali", 120);

	set("combat_exp", 2750000);

	set_skill("force", 290);
	set_skill("yunv-xinfa", 290);
	set_skill("surge-force", 290);
	set_skill("sword", 280);
	set_skill("yunv-jian", 280);
	set_skill("quanzhen-jian", 280);
	set_skill("xuantie-jian", 280);
	set_skill("dodge", 250);
	set_skill("yunv-shenfa", 250);
	set_skill("parry", 285);
	set_skill("unarmed", 285);
	set_skill("meinv-quan", 270);
	set_skill("strike", 280);
	set_skill("sad-strike", 280);
	set_skill("fireice-strike", 280);
	set_skill("tianluo-diwang", 260);
	set_skill("literate", 150);
	set_skill("taoism", 80);
	set_skill("medical", 180);
	set_skill("yunv-xinjing", 180);
	set_skill("throwing", 240);
	set_skill("yufeng-zhen", 240);

	map_skill("force", "surge-force");
	map_skill("sword", "xuantie-jian");
	map_skill("dodge", "yunv-shenfa");
	map_skill("parry", "meinv-quan");
	map_skill("unarmed", "sad-strike");
	map_skill("strike", "tianluo-diwang");

	prepare_skill("unarmed", "sad-strike");

	create_family("��Ĺ��", 3, "����");

	set("inquiry", ([
		"������" : "��...�٣�",
		"����"   : "�������������Ĵ�����",
		"����"   : "��ʦ��ô...�治��˵����",
		"С��Ů" : "����������Ӹ�ʲô��",
		"�"   : "���ˣ�������Ҳ�ա�",
		"�����" : "����ͷ��û�У��ܾ�û�������ˡ�",
	]));

	set("guarder", ([
		"refuse_home" : "$N��$n�����������",
		"refuse_other": "$N��$n���������ǹ�Ĺ���������ĵط�������Ҫ���ţ�",
		"refuse_carry": "$N��$n�ȵ����������ϵ��˸������£�",
	]));

	set("no_teach/sad_strike", (: not_to_learn_ss :));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "strike.wang" :),
		(: perform_action, "unarmed.sad" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();

	carry_object("/clone/cloth/qingyi")->wear();
}

int not_to_learn_ss(object ob)
{
	if (ob->query("gender") == "Ů��")
	{
		command("say �������书���ʺ�Ů����ѧϰ���������˰ɣ�");
		return 1;
	}

	if (ob->query_temp("can_learn/yang/sad-strike"))
		return 0;

	if (ob->query("static/sadly") < 3)
	{
		command("say ����᲻������˼�����ӵ��黳��"
			"�޷�����ҵ���Ȼ�����ƣ�");
		return 1;
	}

	message_vision("$n���˿�$N�������ã�����Ҳ��������"
		       "ԨԴ���Ҿʹ�����Ȼ�����ƣ�\n",
		       ob, this_object());
	ob->set_temp("can_learn/yang/sad-strike", 1);
	return 0;
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("family/family_name") == query("family/family_name"))
	{
		if (query_skill(skill) < 1 ||
		    SKILL_D(skill)->type() != "martial")
			return 0;

		if (ob->query_int() < 32)
		{
			command("say ���������ʲ��ѣ��ҽ�����̫�ۡ�");
			return -1;
		}

		return 1;
	}

	if (skill == "unarmed" &&
	    this_player()->query_skill("sad-strike", 1) > 0 &&
	    this_player()->query_skill(skill, 1) < 180)
		return 1;

	if (skill != "sad-strike")
	{
		command("say �㻹�������ʦ��ȥѧϰ�ɣ�");
		return 0;
	}

	if (not_to_learn_ss(ob))
		return -1;

	return 1;
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query_int() < 32)
	{
		command("say ������ʲ�������������ϳ��书��");
		return;
	}

	if ((int)ob->query_skill("force") < 150)
	{
		command("say �����Ϊʦô������ڹ������������ɣ�");
		return;
	}

	if ((int)ob->query("max_neili") < 1000)
	{
		command("say �������������������Ҳ���ٰ���");
		return;
	}

	command("say �ðɣ�����Ҳ���������ˣ��Ҿ����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
}

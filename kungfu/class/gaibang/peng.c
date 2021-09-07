#include <ansi.h>

inherit NPC;
inherit F_MASTER;

mixed ask_me(); 
#include "gaibang.h"

void consider();

void create()
{
	set_name("���о�", ({"peng youjing", "peng", "youjing"}));
	set("title", "ؤ��Ŵ�����");
	set("nickname", "�Ʋ���ͷ");
	set("gender", "����");
	set("age", 50);
	set("long", 
		"���о���ؤ���о����ɵ����죬���Ÿɾ�����������л��ӡ�\n"
		"�����Ϲ��Ŵ����Ц�ݣ�һ˫�۾����������ǵ�������\n");

	set("attitude", "peaceful");
	
	set("str", 28);
	set("int", 27);
	set("con", 24);
	set("dex", 25);

	set("qi", 2000);
	set("max_qi", 2000);
	set("jing", 1000);
	set("max_jing", 1000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 70);
	set("shen_type", -1);
	
	set("combat_exp", 850000);
	set("score", 20000);
	
	set_skill("force", 170);
	set_skill("jiaohua-neigong", 170);
	set_skill("unarmed", 165);
	set_skill("changquan", 165);
	set_skill("dodge", 160);
	set_skill("feiyan-zoubi", 160);
	set_skill("parry", 170);
	set_skill("staff", 180);
	set_skill("fengmo-zhang", 180);

	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("parry", "fengmo-zhang");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("staff", "fengmo-zhang");

	create_family("ؤ��", 18, "�Ŵ�����");

	set("inquiry", ([
		"��ħ�ȷ�" : (: ask_me :),
	]));

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
	}) );

	setup();

	carry_object("/clone/weapon/tiegun")->wield();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob)) return;

	if ((int)ob->query_str() < 26)
	{
		command("say ����ؤ�������һ���Ը���Ϊ����" + 
		RANK_D->query_respect(ob) + "�������У��ƺ�����ѧؤ��Ĺ���");
		return;
	}

	if (ob->query_skill("force") < 150)
	{
		command("say ����ڹ���򻹲��У��Ⱥͱ��ʦ��ѧϰ�ɡ�");
		return;
	}

	command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
		"�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");

	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/fengmo-zhang/qunmo"))
		return "�㲻���Ѿ������𣿴��������Ҵ�ѽ��";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "�γ����ԣ�";

	if (me->query("beggarlvl") < 6)
		return "���ڰ���ı���̫���ˣ����㵽�������Ӻ��������Ұɣ�";

	if (me->query_skill("fengmo-zhang", 1) < 150)
		return "��ķ�ħ�ȷ��������ң�Ҫ��������";

	message_vision( HIY "$n" HIY "���˵�ͷ��ͻȻһ�����ȣ�"
			"��������һ�����裬�����������Ӱ������"
			"���ȣ������ɵ���\n���Ƿ�ħ�ȷ��ľ�Ҫ���ڣ�"NOR"\n",
			me, this_object());
	command("haha");
	command("say �����ˣ�");
	tell_object(me, HIC "��ѧ���ˡ�Ⱥħ���衹��һ�С�"NOR"\n");
	if (me->can_improve_skill("staff"))
		me->improve_skill("staff", 160000);
	me->set("can_perform/fengmo-zhang/qunmo", 1);
	return 1;
}

int recognize_apprentice(object me)
{
	if (me->query("family/family_name") != query("family/family_name"))
		return 0;

	if (me->query("beggarlvl") < 9)
		return 0;

	return 1;
}

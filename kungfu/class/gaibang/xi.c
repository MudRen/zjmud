#include <ansi.h>

inherit NPC;
inherit F_MASTER;

mixed ask_me(); 
#include "gaibang.h"

void consider();

void create()
{
	set_name("�ɳ���", ({"xi zhanglao", "xi", "zhanglao"}));
	set("title", "ؤ��Ŵ�����");
	set("gender", "����");
	set("age", 45);

	set("attitude", "peaceful");
	set("str", 35);
	set("int", 21);
	set("con", 32);
	set("dex", 25);

	set("qi", 2500);
	set("max_qi", 2500);
	set("jing", 1200);
	set("max_jing", 1200);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 80);
	
	set("combat_exp", 1000000);
	set("shen_type", 1);
	set("score", 25000);
	
	set_skill("force", 180);
	set_skill("jiaohua-neigong", 180);
	set_skill("unarmed", 180);
	set_skill("changquan", 150);
	set_skill("dodge", 150);
	set_skill("feiyan-zoubi", 150);
	set_skill("parry", 180);
	set_skill("staff", 180);
	set_skill("fumo-zhang", 180);
	set_skill("begging", 150);
	set_skill("checking", 150);
	set_skill("jueming-tui", 180);

	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "jueming-tui");
	map_skill("parry", "fumo-zhang");
	map_skill("staff", "fumo-zhang");
	map_skill("dodge", "feiyan-zoubi");
	
	set("inquiry", ([
		"��ħ��": (: ask_me :),
	]));

	create_family("ؤ��", 18, "�Ŵ�����");

	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: perform_action, "staff.lun" :),
		(: exert_function, "recover" :),
	}) );

	setup();

	carry_object("/clone/weapon/gangzhang")->wield(); 
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
	if (me->query("can_perform/fumo-zhang/lun"))
		return "�Լ��úö���ϰ�ɣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "�γ����ԣ�";

	if (me->query("beggarlvl") < 8)
		return "���ڰ���ı���̫���ˣ����㵽�˴����Ӻ��������Ұɣ�";

	if (me->query_skill("fumo-zhang", 1) < 150)
		return "��ķ�ħ�Ȼ������ң�Ҫ��������";

	message_vision( HIY "$n" HIY "΢Ц�ŵ��˵�ͷ��ͻȻһ�����ȣ�"
			"�������Ȼ��裬��Ӱ������������Ȧ����\nͬ" NOR +
			HIR "�����" NOR + HIY "һ�㣬������磬����"
			"΢���ޱȣ�"NOR"\n",
			me, this_object());
	command("nod");
	command("say ��������ˣ�");
	tell_object(me, HIC "��ѧ���ˡ�����֡���һ�С�"NOR"\n");
	if (me->can_improve_skill("staff"))
		me->improve_skill("staff", 160000);
	me->set("can_perform/fumo-zhang/lun", 1);
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

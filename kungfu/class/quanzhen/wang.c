// wang.c ������
#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

string ask_jiuyin();
string ask_duan();
mixed  ask_hua();
mixed  ask_hup();

void create()
{
	set_name("������", ({"wang chongyang", "wang"}));
	set("gender", "����");
	set("age", 66);
	set("class", "taoist");
	set("nickname",HIW"������"NOR);
	set("long", "������ȫ��̵Ŀ�ɽ��ʦ���״��ƽ������������ˡ�������Ʈ"
			"Ʈ�����ۻ��䣬üĿ��񳣬����Щ�ɷ���ǵ�ζ����������һ"
			"ǻ��Ѫ����Ч���������������ϧ��͢���ܣ������Ļ����䣬"
			"�ִӵ��¾����������������Ĵ�����ִ�ȫ��̡�");
	set("attitude", "peaceful");
	set("shen_type",1);

	set("str", 32);
	set("int", 35);
	set("con", 33);
	set("dex", 31);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
		(: perform_action, "sword.hua" :),
		(: perform_action, "sword.ding" :),
		(: perform_action, "sword.chan" :),
		(: perform_action, "finger.qiankun" :),
		(: perform_action, "strike.ju" :),
	}));

	set("qi", 6500);
	set("max_qi", 6500);
	set("jing", 3200);
	set("max_jing", 3200);
	set("neili", 7800);
	set("max_neili", 7800);
	set("jiali", 100);
	set("combat_exp", 2850000);

	set_skill("force", 280);
	set_skill("quanzhen-xinfa", 280);
	set_skill("xiantian-gong", 280);
	set_skill("sword", 260);
	set_skill("quanzhen-jian",260);
	set_skill("dodge", 260);
	set_skill("jinyan-gong", 260);
	set_skill("parry", 280);
	set_skill("jinguan-yusuo", 280);
	set_skill("strike", 260);
	set_skill("chongyang-shenzhang", 260);
	set_skill("haotian-zhang", 260);
	set_skill("literate", 200);
	set_skill("finger", 260);
	set_skill("taoism", 300);
	set_skill("finger", 260);
	set_skill("zhongnan-zhi", 260);
	set_skill("sun-finger", 260);
	set_skill("medical", 280);
	set_skill("liandan-shu", 280);

	map_skill("force", "xiantian-gong");
	map_skill("sword", "quanzhen-jian");
	map_skill("dodge", "jinyan-gong");
	map_skill("parry", "jinguan-yusuo");
	map_skill("finger","sun-finger");
	map_skill("strike", "haotian-zhang");

	prepare_skill("finger", "sun-finger");
	prepare_skill("strike", "haotian-zhang");

	set("no_teach/sun-finger", "һ��ָ�Ƕμ��ش����Ҳ��ܽ��㡣");

	create_family("ȫ���", 1, "�ƽ�");

	set("book_count",1);
	set("inquiry", ([
		"ȫ���" :  "��ȫ��������µ����������ڡ�\n",
		"�����澭" : (: ask_jiuyin :),
		"�λ�ү"   : (: ask_duan :),
		"������Ԫ" : (: ask_hup :),
		"һ��������": (: ask_hua :),
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.ding" :),
		(: perform_action, "sword.hua" :),
		(: perform_action, "strike.ju" :),
		(: perform_action, "finger.qiankun" :),
		(: perform_action, "finger.dian" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/quanzhen/npc/obj/greenrobe")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query_int() < 35)
	{
		command("say ������Ի������������������Ǽ���ͽ��ѧϰ�ɡ�");
		return;
	}

	if ((int)ob->query_skill("quanzhen-xinfa", 1) < 100)
	{
		command("say ��ı����ڹ��ķ�����㣬ֻ������"
			"���Ը�������书��");
		return;
	}

	if (ob->query("combat_exp") < 200000)
	{
		command("say ���ʵս����̫������������Ը�������书��");
		return;
	}

	if ((int)ob->query("shen") < 100000)
	{
		command("say �����������ұ�ѧ���˵���ּ�������Щ��"
			"��֮�£��ҷ�������Ϊͽ��\n");
		return;
	}
	command("say �ðɣ��������ʣ����ɴ����²����Ҿ����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
}

string ask_jiuyin()
{
	int lvl_force;

	if (this_player()->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(this_player()) +
		"�뱾�̺��޹ϸ��⻰�Ӻ�˵��";

	if ((lvl_force = this_player()->query_skill("force", 1)) < 50)
		return RANK_D->query_respect(this_player()) +
		"�Ļ����ڹ�������֮ǳ��ǿ���澭�ϵ��ϳ��书�к����档";

	return "�����澭��������ѧ���ڣ����ѽ�����ʦ���ܲ�ͨ���ܡ�";
}

string ask_duan()
{
	return "���ʶλ�ү����ô��Ī��������Ϊ�ѣ�\n"; 
}

mixed ask_hua()
{
	object me;

	me = this_player();
	if (me->query("can_perform/quanzhen-jian/hua"))
		return "�ú�����ȥ�ɣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�㻹��������ȫ������˵�ɣ�";

	if (me->query_skill("xiantian-gong", 1) < 100)
		return "ʹ��һ����������Ҫ�����칦Ϊ���������Ȱѻ��������˵��";

	if (me->query_skill("quanzhen-jian", 1) < 100)
		return "���ȫ�潣�����ܲ����ң���������˵��";

	message_vision(HIC "$n" HIC "˺��һ�ǲ���������������ʱ��"
		       "����ͬ���������̴ִ�������޷����������ѳ�"
		       "�����������$N" HIC "Ŀ�ɿڴ���"NOR"\n",
		       me, this_object());
	command("say ������������еİ��أ�");
	tell_object(me, HIG "��ͨ����һ��������İ��"NOR"\n");
	if (me->can_improve_skill("force"))
		me->improve_skill("force", 90000);
	me->set("can_perform/quanzhen-jian/hua", 1);
	me->set("neili", 0);
	return 1;
}

mixed ask_hup()
{
	object me;

	me = this_player();
	if (me->query("can_perform/xiantian-gong/hup"))
		return "�㻹�Ǻú�����ȥ�ɣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�㻹��������ȫ������˵�ɣ�";

	if (me->query_skill("xiantian-gong", 1) < 200)
		return "�㻹��Ҫ�úö������칦���������һ����ͣ�";

	message_sort("$N���������дʵ����������ˣ���ǿ����ǿ�����"
		     "��ɽ�ڣ��к�... ��$n�ɻ���������... ������"
		     "��ô��Щ���죿��$N���ɵ����ѣ�æ������������"
		     "˼�������˾����񹦵Ŀھ��ˡ�����������˵��"
		     "�ӿڴ����ͳ�һ���������õ�С���ӣ����˰��죬"
		     "ָ������һ�ζ�$n˵���������ţ������û���ˡ�"
		     "��$n���˰��죬Ĭ�������С�$N�������������ú�"
		     "��ȥ�ɣ���Ҫ������ȫ��̶���������\n", this_object(), me);
	tell_object(me, HIG "��ͨ����������Ԫ�İ��"NOR"\n");
	if (me->can_improve_skill("force"))
		me->improve_skill("force", 90000);
	me->set("can_perform/xiantian-gong/hup", 1);
	return 1;
}

void unconcious()
{
	die();
}



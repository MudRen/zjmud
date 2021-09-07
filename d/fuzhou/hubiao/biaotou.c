
#include <ansi.h>

inherit "/kungfu/class/generate/chinese";

void create()
{
	mapping name;
	int i;
	string *fams;

	name = NPC_D->get_cn_name();
	set_name("����ʦ", name["id"]);
	set("title", HIW"�����ھ���ʦ"NOR);
	set("gender", (i==0?"Ů��":"����"));
	set("age", 35 +random(30));
	set("combat_exp", 100000);
	set("attitude", "friendly");
	set("int", 25+random(5));
	set("con", 25+random(5));
	set("dex", 25+random(5));
	set("str", 25+random(5));
	set("per", 25);
	set("biaotou", 1);

	set("chat_chance", 2);
        set("chat_msg",({
		CYN+query("name")+"�ȵ����������˵������ˡ���"NOR"\n",
		CYN+query("name")+"�ȵ��������߿��ߣ���͵������"NOR"\n",
	}));

	set_skill("literate", query("int") * 10);

	set("location",1);
	setup();
	fams = keys(init_family);
	setup_family(fams[random(sizeof(fams))]);
}

void heart_beat()
{
	object me = this_object();
	object where;

	if ( ! me) return;
	if ( !environment(me)) return;

	if ( me->query_temp("protecting")) {
		where = environment(me->query_temp("protecting"));
		if ( where && environment(me) != where)
			me->move(where);
	}
	::heart_beat();
}

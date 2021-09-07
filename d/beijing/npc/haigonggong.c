#include <ansi.h>
inherit NPC;

string ask_for_zigong();
int ask_for_gongzi();

void create()
{
	set_name("������", ({"hai gonggong", "hai", "gonggong"}));
	set("title", HIR "����ǧ��" NOR);
	set("long", "���Ƕ�����̫�ຣ�󸻣����ü�����"
		    "ͷ������̫̫��\n"
	);
	set("gender", "����");
	set("rank_info/respect", "����");
	set("attitude", "heroism");
	set("class", "eunach");

	set("inquiry",([
		"�Թ�"    : (: ask_for_zigong :),
	]));

	set("age", 60);
	set("shen_type", -1);
	set("str", 25);
	set("int", 20);
	set("con", 20);
	set("dex", 25);
	set("max_qi", 2000);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 100);
	set("combat_exp", 150000);
	set("score", 100);
	set("apply/attack",  100);
	set("apply/defense", 100);

	set_skill("force", 120);
	set_skill("unarmed", 120);
	set_skill("sword", 120);
	set_skill("dodge", 120);
	set_skill("parry", 120);
	set_skill("pixie-jian", 120);

	map_skill("dodge", "pixie-jian");
	map_skill("sword", "pixie-jian");
	map_skill("unarmed", "pixie-jian");
	map_skill("parry", "pixie-jian");

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object(__DIR__"obj/cloth3")->wear();
	add_money("silver", 50);
}

void init()
{
	add_action("do_decide", "decide");
}

string ask_for_zigong()
{
	object me;

	me = this_player();

	if ((string)me->query("gender") == "����")
		return "����ͬ�����ˣ��αؿ�������ĵ���Ц��\n";

	if ((string)me->query("gender") == "Ů��")
		return "�����ѷϣ���һ�����Ը������С���˴������֣�Ҫ��Ҫ���ԣ�\n";

	if ((int)me->query("age") > 30)
		return "��Ҫ������ô������������˴�뱲�Ӳ��Թ����ҵ��ǵ�һ����˵��( �������䲻�ܴ���30�� )\n";

	if ((int)me->query_str() > 30)
		return "��λ�ú����ڴ�׳���Թ��а���հ�����ף����ס�( ���ﵱǰ�������ܴ���30 )\n";

	me->set_temp("pending/zigong", 1);
		return "�Թ�����λ������ò���ã��α�... ����ϣ����������Ǹ���\n"
		       "���������ŵ����Թ�֮�󣬲��ɺ�ڣ����������Ѷ�" HIR "(de"
		       "cide)" NOR + CYN "�͸����ҡ�"NOR"\n";
}

int do_decide()
{
	object me;

	me = this_player();
	if (! me->query_temp("pending/zigong"))
		return 0;

	message_vision(HIC "����̾�˿�����������Ȼ��������С���ӣ��������Ҹ���"
		       "λ" HIC + RANK_D->query_respect(me) + HIC "����\n������"
		       "��$N" HIC "˵�����ðɣ����ɵ�������ȥ�������Ҫ��ʼ�ˡ�\n"
		       "\n$N" HIC "һҧ�������ϰ��壬���������¡�"NOR"\n" + HIR
		       "$n" HIR "ҡ��ҡͷ����������嵽$N" HIR "����֮�䣬����һ"
		       "�࡭����\n\n$N" HIR "��ʱ�ҽ�һ�����˹�ȥ����"NOR"\n",
		       this_player(), this_object());

	command("chat �������󸻽���Ϊ" + me->name(1) + "���������빬֮��");

	me->delete_temp("pending/zigong");
	me->set("gender","����");
	me->set("class", "eunach");
	me->add("combat_exp", 1000);
	me->unconcious();
	return 1;
}


inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
	set_name("�����վ���", ({ "shenzhao jing", "shenzhao", "jing" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ�������ľ��飬������д�š����վ����������֡�\n" );
		set("value", 1);
		set("no_sell", 1);
		set("material", "paper");
		set("skill", ([
			"name"	: "shenzhaojing",
			"exp_required":  100000,
			"jing_cost"   :  120,
			"difficulty"  :  40,
			"max_skill"   :  180,
			"min_skill"   :  40,
		]) );
	}
}

int query_autoload() { return 1; }



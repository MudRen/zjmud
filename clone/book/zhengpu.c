// zhengpu.c

inherit ITEM;

void create()
{
	set_name("����", ({ "qin pu", "pu" }));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����������ף�������һЩ������ݵķ�����\n");
		set("value", 10);
		set("material", "paper");
		set("skill", ([
			"name": 	"guzheng-jifa",
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	150,
			"min_skill":    10,
		]) );
	}
}


// xiaopu.c

inherit ITEM;

void create()
{
	set_name("����", ({ "xiao pu", "pu" }));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����������ף�������һЩ����ķ�����\n");
		set("value", 10);
		set("material", "paper");
		set("skill", ([
			"name": 	"chuixiao-jifa",
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	150,
			"min_skill":    10,
		]) );
	}
}


// jiyin3.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
	set_name("�������澭���б�", ({ "jiuyin zhenjing3" }));
	set_weight(400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���ֳ����������¼��һЩ�书�ؾ���\n");
		set("value", 0);
		set("no_put", 1);
		set("material", "paper");
		set("skill", ([
			"name":	"force",
			"exp_required": 100000,
			"jing_cost" : 45,
			"difficulty": 30,
			"max_skill" : 149,
			"min_skill" : 100
		]) );
	}
}

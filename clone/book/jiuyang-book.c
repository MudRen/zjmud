// jiuyang.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
	set_name("�������澭��", ({ "jiuyang zhenjing", "jiuyang", "zhenjing" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"����һ�������ľ��飬ֻ���Ͳ����ý��ܣ��䳤�ڲ���Գ��֮�У���ҳ��Ȼ�������
������д�������������������֣���һ��Ҳ��ʶ�ã�������һ�����ı����о�����Щ��
�ģ���ÿһ��֮�䣬ȴ��ӬͷС��д�����й����֡�\n",
	);
		set("value", 1);
		set("no_sell", 1);
		set("material", "paper");
		set("skill", ([
			"name"	: "jiuyang-shengong",
			"exp_required":  100000,
			"jing_cost"   :  120,
			"difficulty"  :  40,
			"max_skill"   :  180,
			"min_skill"   :  30,
		]) );
	}
}

int query_autoload() { return 1; }


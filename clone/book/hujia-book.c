// hujia-book.c

inherit ITEM;

void create()
{
	set_name( "���ҵ����ܾ�",({ "daopu zongjue", "zongjue" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long","���Ǻ��ҵ����ܾ�����¼�˾���ĺ��ҵ�����\n");
		set("value", 50);
		set("material", "paper");
		set("skill", ([
			"name":	 "hujia-daofa",//name of the skill
			"exp_required": 10000 ,       //minimum combat experience required
			"jing_cost":    40,	   // jing cost every time study this
			"difficulty":	32,	   // the base int to learn this skill
			"min_skill":	30,	   // the minimum level you can learn
			"max_skill":	149	   // the maximum level you can learn
		]) );
	}
}

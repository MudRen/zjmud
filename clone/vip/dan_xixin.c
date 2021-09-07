// jinsha.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW "ϴ�ĵ�" NOR, ({ "xixin dan" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ����Ө��͸�ĵ�ҩ���ɶ���һ�����ƶ��ɣ�����֮��ʹ��ǿ��ɢȥ�����书���Ӷ����°�ʦѧ�ա�\n");
		set("unit", "��");
		set("value", 50000);
		set("yuanbao", 1200);
		set("only_do_effect", 1);
		set("weight", 1);
	}
	setup();
}

int do_effect(object me)
{
	string family,*skills;
	int i;
	mapping all_fam = ([
		"�䵱��":({
				"taiji-quan",
				"taiji-shengong",
				"wudang-xinfa",
				"tiyunzong",
				"wudang-zhang",
				"paiyun-shou",
				"wudang-jian",
				"taiji-jian",
				"taiji-dao",
				"raozhi-roujian",
				"huzhua-shou",
				"zhenshan-zhang",
				"yitian-zhang",
				"shenmen-jian",
				"xuanxu-dao",
				"yitian-zhang",
				"shenmen-jian",
			}),
		"������":({
				"jingang-buhuaiti",
                                "banruo-zhang",
                                "jingang-zhi",
                                "jingang-quan",
                                "xumishan-zhang",
				"cibei-dao",
				"damo-jian",
				"fengyun-shou",
				"fumo-jian",
				"hunyuan-yiqi",
				"shaolin-xinfa",
				"jingang-quan",
				"longzhua-gong",
				"luohan-quan",
				"nianhua-zhi",
				"pudu-zhang",
				"qianye-shou",
				"sanhua-zhang",
				"riyue-bian",
				"shaolin-shenfa",
				"weituo-gun",
				"wuchang-zhang",
				"xiuluo-dao",
				"yingzhua-gong",
				"yijinjing",//������180
				"yizhi-chan",
				"zui-gun",
//����Ϊ���ֲؾ��������书
				"yipai-liangsan",
				"xiuluo-zhi",
				"duoluoye-zhi",
				"wuxiang-zhi",
			}),
		"������":({
				"kurong-changong",
				"duanshi-xinfa",
				"tiannan-step",
				"sun-finger",
			}),
		"��ɽ��":({
				"huashan-sword",
				"huashan-xinfa",
				"huashan-quanfa",
				"huashan-shenfa",
				"zixia-shengong",
				"poyu-quan",
				"hunyuan-zhang",
				"feiyan-huixiang",
				"kuangfeng-jian",
				"yunu-sword",
				"fanliangyi-dao",
			}),
		"��ɽ����":({
				"huashan-sword",
				"huashan-xinfa",
				"huashan-quanfa",
				"huashan-shenfa",
				"zixia-shengong",
				"poyu-quan",
				"hunyuan-zhang",
				"feiyan-huixiang",
				"kuangfeng-jian",
				"yunu-sword",
				"fanliangyi-dao",
			}),
		"������":({
				"persuading",
				"jinding-zhang",
				"tiangang-zhi",
				"huifeng-jian",
				"yanxing-dao",
				"zhutian-bu",
				"emei-xinfa",
				"linji-zhuang",
				"piaoxue-zhang",
				"jiuyin-baiguzhao",//����������Ϊ�������ܿ�ѧ��100��
			}),
		"�һ���":({
				"bibo-shengong",
				"luoying-xinfa",
				"tanzhi-shentong",
				"luoying-shenzhang",
				"xuanfeng-leg",
				"anying-fuxiang",
				"luoying-shenjian",
				"yuxiao-jian",
				"lanhua-shou",
				"bihai-chaosheng",
			}),
		"������":({
				"shenlong-xinfa",
				"yixingbu",
				"shenlong-bashi",
				"huagu-mianzhang",
				"shedao-qigong",
			}),
		"ؤ��":({
				"jiaohua-neigong",
				"huntian-qigong",
				"changquan",
				"xiaoyaoyou",
				"feiyan-zoubi",
				"dragon-strike",//������ѧ���賴��
				"jiaohua-bangfa",
				"dagou-bang",
				"mantianhuayu-zhen",
				"jueming-tui",
				"chansi-shou",//������
				"suohou-gong",//���Ԫ
				"fengmo-zhang",//���о�
				"fumo-zhang",//jian
				
			}),
		"��Ĺ��":({
				"yunv-xinfa",
				"surge-force",
				"yunv-jian",
				"quanzhen-jian",
				"xuantie-jian",
				"yunv-shenfa",
				"meinv-quan",
				"sad-strike",//����
				"fireice-strike",
				"tianluo-diwang",
				"yufeng-zhen",
				"yinsuo-jinling",
				"tianluo-diwang",
			}),
		"ȫ���":({
				"quanzhen-xinfa",
				"xiantian-gong",
				"quanzhen-jian",
				"jinyan-gong",
				"jinguan-yusuo",
				"chongyang-shenzhang",
				"haotian-zhang",
				"zhongnan-zhi",
			}),
		"������":({
				"huagong-dafa",
				"freezing-force",
				"guixi-gong",
				"feixing-shu",
				"zhaixinggong",
				"chousui-zhang",
				"sanyin-wugongzhao",
				"chanhun-suo",
				"tianshan-zhang",
			}),
		"��ң��":({
				"xiaoyao-xinfa",
				"beiming-shengong",
				"xiaowuxiang",
				"lingbo-weibu",
				"feiyan-zoubi",
				"liuyang-zhang",
				"ruyi-dao",
				"zhemei-shou",
			}),
		"ѩɽ��":({
				"longxiang",
				"mizong-neigong",
				"mingwang-jian",
				"xiangmo-chu",
				"riyue-lun",
				"shenkong-xing",
				"dashou-yin",
				"yujiamu-quan",
				"xiaowuxiang",
				"huoyan-dao",
			}),
		"Ѫ����":({
				"xue-dao",
				"mingwang-jian",
				"mizong-neigong",
				"xuehai-mogong",
				"shenkong-xing",
				"dashou-yin",
				"yujiamu-quan",
			}),

		"���չ�":({
				"zhemei-shou",
				"liuyang-zhang",
				"yueying-wubu",
				"bahuang-gong",
				"tianyu-qijian",
				"lingjiu-xinfa",
				"zhougong-jian",
			}),
		"Ľ������":({
				"zihui-xinfa",
				"douzhuan-xingyi",
				"beidou-xianzong",
				"canhe-zhi",
				"qixing-quan",
				"murong-sword",
				"longcheng-shendao",
			}),
		"ŷ������":({
				"shedu-qiqiao",
				"hamagong",
				"chanchu-bufa",
				"lingshe-quan",
				"lingshe-zhangfa",
				"baibian-daxue",
			}),
		"�������":({
				"lengyue-shengong",
				"hujia-daofa",
				"taxue-wuhen",
				"sixiang-bufa",
				"mantian-xing",
				"tianchang-zhang",
				"hujia-quan",
				"baisheng-daofa",
				"miaojia-jian"
			}),
		"���ϻ���":({
				"duanshi-xinfa",
				"tiannan-step",
				"jinyu-quan",
				"duanjia-sword",
				"sun-finger",
				"wuluo-zhang",
				"feifeng-whip",//���׷�
				"qingliang-daxuefa",//�쵤��
				"yuezhao-gong",//hua
			}),
	]);

	if(!me->query("family"))
	{
		tell_object(me,"�㻹û��ʦ�Űɣ�����ʹ��"+query("name")+"��\n");
		return 0;
	}
	message_vision(CYN "$N" CYN "С�ĵķ�����һ"+query("unit")+"" + name() + CYN "�������������ˡ�"NOR"\n", me);

	family = me->query("family/family_name");
	if(skills=all_fam[family])
	{
		for(i=0;i<sizeof(skills);i++)
		{
			me->delete_skill(skills[i]);
		}
	}
	else
	{
		tell_object(me,"�������ݴ�������ϵ����Ա��\n");
		return 0;
	}
	CHANNEL_D->do_channel( this_object(), "rumor","��˵"+me->query("name")+"������һ��"+this_object()->query("name")+""HIM"�������һ������ѡ��ʦ�ŵĻ��ᣡ");
	me->delete("family");
	me->delete("title");
	me->delete("class");
	destruct(this_object());

	return 1;
}
int query_autoload() { return 1; }
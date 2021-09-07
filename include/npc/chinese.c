// chinese name

// ���µ����ݣ�
// mapping get_cn_name() - ����һ��������� & ID

#include "name.h"

mapping get_cn_name();

mapping cn_sname = ([
	"��" : "bai",
	"��" : "cai",
	"��" : "cao",
	"��" : "chen",
	"��" : "dai",
	"�" : "dou",
	"��" : "deng",
	"��" : "di",
	"��" : "du",
	"��" : "duan",
	"��" : "fan",
	"��" : "fan",
	"��" : "fang",
	"��" : "feng",
	"��" : "fu",
	"��" : "fu",
	"��" : "gao",
	"��" : "gu",
	"��" : "guan",
	"��" : "guo",
	"ë" : "mao",
	"��" : "han",
	"��" : "hu",
	"��" : "hua",
	"��" : "hong",
	"��" : "hou",
	"��" : "huang",
	"��" : "jia",
	"��" : "jiang",
	"��" : "jin",
	"��" : "liao",
	"��" : "liang",
	"��" : "li",
	"��" : "lin",
	"��" : "liu",
	"��" : "long",
	"½" : "lu",
	"¬" : "lu",
	"��" : "luo",
	"��" : "ma",
	"ţ" : "niu",
	"��" : "pang",
	"��" : "pei",
	"��" : "peng",
	"��" : "qi",
	"��" : "qi",
	"Ǯ" : "qian",
	"��" : "qiao",
	"��" : "qin",
	"��" : "qiu",
	"��" : "qiu",
	"��" : "qiu",
	"ɳ" : "sha",
	"��" : "shang",
	"��" : "shang",
	"��" : "shao",
	"��" : "shen",
	"ʦ" : "shi",
	"ʩ" : "shi",
	"��" : "song",
	"��" : "sun",
	"ͯ" : "tong",
	"��" : "wan",
	"��" : "wang",
	"κ" : "wei",
	"��" : "wei",
	"��" : "wu",
	"��" : "wu",
	"��" : "xiao",
	"Ф" : "xiao",
	"��" : "xiang",
	"��" : "xu",
	"��" : "xu",
	"Ѧ" : "xue",
	"��" : "yang",
	"��" : "yang",
	"��" : "yang",
	"��" : "yi",
	"��" : "yin",
	"��" : "yu",
	"��" : "zhao",
	"��" : "zhong",
	"��" : "zhou",
	"֣" : "zheng",
	"��" : "zhu",

	"����" : "dongfang",
	"����" : "dugu",
	"Ľ��" : "murong",
	"ŷ��" : "ouyang",
	"˾��" : "sima",
	"����" : "ximen",
	"ξ��" : "yuchi",
	"����" : "zhangsun",
	"���" : "zhuge",
	"�Ϲ�" : "shangguan",
	"�ĺ�" : "xiahou",
	"����" : "wenren",
	"�ʸ�" : "huangfu",
	"�̨" : "tantai",
	"����" : "gongzhi",
	"����" : "chunyu",
	"����" : "shentu",
	"����" : "gongsun",
	"����" : "gongyang",
	"��ԯ" : "xuanyuan",
	"���" : "linghu",
	"����" : "zhongli",
	"����" : "yuwen",
	"Ľ��" : "murong",
	"����" : "zhongsun",
	"˾ͽ" : "situ",
	"˾��" : "sikong",
	"��ľ" : "duanmu",
	"����" : "gongliang",
	"����" : "baili",
	"����" : "dongguo",
	"�Ϲ�" : "nanguo",
	"����" : "huyan",
	"����" : "yangshe",
	"����" : "dongmen",
	"�Ϲ�" : "nangong",
]);

mapping cn_pname = ([
	"ai"   : "������",
	"an"   : "������",
	"ao"   : "�°�����",
	"ang"  : "����",
	"ba"   : "�հ�",
	"bai"  : "�װ�",
	"ban"  : "�߰�",
	"bang" : "��",
	"bei"  : "��������",
	"biao" : "������",
	"bian" : "�߱�����",
	"bu"   : "����",
	"cao"  : "�ܲݲ���",
	"cang" : "�Բ�",
	"chang": "���������`",
	"chi"  : "�ٳֳس�߳۳�",
	"ci"   : "�˴δʴĴǴ�",
	"du"   : "����",
	"dong" : "����",
	"dou"  : "��",
	"fa"   : "������",
	"fan"  : "����������ެ",
	"fang" : "�������P",
	"feng" : "���������",
	"fu"   : "�����ܽ",
	"gao"  : "�߸�۬��",
	"hong" : "����������",
	"hu"   : "���������������",
	"hua"  : "����������",
	"hao"  : "�ź������尜B",
	"ji"   : "�����ü������������Ǽͼ��̼��Ƽ����ʼ����ɼ������ܸ"
		 "���٥��ڵ������",
	"jian" : "�������������",
	"kan"  : "���",
	"ke"   : "�ɿ˿ƿ�����۠�",
	"lang" : "����������ݹ",
	"li"   : "������������������������������",
	"lin"  : "��������",
	"ma"   : "��", 
	"mao"  : "óðòð�ìî�",
	"miao" : "�����",
	"nan"  : "���",
	"pian" : "Ƭ��",
	"qian" : "Ǳǫٻ��Ǭ�ǧ",
	"qiang": "ǿǼﺫo",
	"qin"  : "������������",
	"qing" : "��������",
	"ran"  : "ȽȻȾȼ",
	"ren"  : "��������",
	"sha"  : "ɳɷ",
	"shang": "������",
	"shen" : "������������ݷ",
	"shi"  : "ʦʷʯʱʮ��ʿʫʼʾ����",
	"shui" : "ˮ",
	"si"   : "˼˹˿˾������",
	"song" : "������",
	"tang" : "�������",
	"tong" : "ͳͨͬͯͮ��",
	"tian" : "������",
	"wan"  : "������",
	"wei"  : "��΢ΰά��Τγ�Ω��Ϊ",
	"wu"   : "����������������أ����",
	"xi"   : "��ϯ��ϴϦ����ϧ",
	"xiao" : "����Ц��Ф����У",
	"xiong": "����",
	"yang" : "��������������r��",
	"yi"   : "��������������������������������������������ܲ��������",
	"yin"  : "��������������طӝ����",
	"ying" : "ӳӢӰӱ��ӦӨ۫ӥ",
	"you"  : "��������������",
	"yu"   : "����Ԣ����������Ԥ���������������������ع��خԥԣ�����",
	"zhi"  : "����ֵ֪������־ֱ��ִֹ��ּ֥����ֿۤ������",
	"zhong": "��������",
	"zhou" : "����������",
	"zhu"  : "����פ��ף��������",
	"zhuo" : "׿����׾����ߪ����",
	"zi"   : "����������������",
	"zong" : "����",
	"zu"   : "��������",
	"zuo"  : "����������",
]);

void generate_cn_name(object ob)
{
	mapping ret;

	if (! ob) return;

	ret = get_cn_name();

	ob->set_name(ret["name"], ret["id"]);
}

mapping get_cn_name()
{
	string sname, pname, pname2, id1, id2;
	string *ks, *kp;

	ks = keys(cn_sname);
	kp = keys(cn_pname);
	sname = ks[random(sizeof(ks))];
	id1 = cn_sname[sname];
	for (;;)
	{
		pname = kp[random(sizeof(kp))];
		if (pname != id1 &&
		    ! find_living(id1 + " " + pname))
			break;
	}

	id2 = pname;
	pname = cn_pname[pname];
	pname = pname[(random(sizeof(pname)) & 0xFFFE)..<1];
	pname = pname[0..1];
	if (random(3) == 0)
	{
		for (;;)
		{
			pname2 = kp[random(sizeof(kp))];
			if (pname2 != id1 && pname2 != pname &&
			    ! find_living(id1 + " " + pname + pname2)) break;
		}
		id2 += pname2;
		pname2 = cn_pname[pname2];
		pname2 = pname2[(random(sizeof(pname2)) & 0xFFFE)..<1];
		pname2 = pname2[0..1];
	} else
		pname2 = "";
		
	return ([ "name" : sname + pname + pname2,
		  "id"   : ({ id1 + " " + id2, id1, id2, }), ]);
}

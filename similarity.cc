/* Baidu 2014 Campus Hiring
 *      Sep 21, 2013
 *
 *  相似度计算用于衡量对象之间的相似程度，在数据挖据、自然语言处理中是一个
 *  基础性计算，在广告检索服务中往往也会判断网民检索Query和广告Adword的主
 *  题相似度。假设Query或者Adword的主题属性定义为一个长度为100000的浮点数据
 *  Pr[100000](称之为主题概率数组)，其中Pr[i]表示Query或者Adword属于主题Id为
 *  i的概率，而Query和Adword的相似度简化定义为两者主题概率数组的内积，即
 *
 *  sim(Query, Adword) = sum(QueryPr[i]*AdwordPr[i])(0<=i<100000).
 *
 *  在实际应用场景中，由于大多数主题的概率都为0，所以主题概率数组往往比较稀
 *  疏，在实现时会以一个紧凑型数组topic_info_t[]的方式保存，其中100<=数组大
 *  小<=10000，并按照topic_id递增排列，0<=topic_id<100000, 0<topic_pr<1.
 *
 *      struct topic_info_t{
 *          int topic_id;
 *          double topic_pr;
 *      };
 *
 *  现在给出Query的topic_info_t数组和N(N>=5000)个Adwords的topic_info_t数组，
 *  现要求出Query与Adwords的相似度最大值，即max(sim(Query,Adword[i])(0<=i<N).
 *
 *  double max_sim(const vector<topic_info_t>& query_topic_info,
 *                  const vector<topic_info_t> adwords_topic_info[],
 *                  int adwords_number);
 *
 *  编写代码求时间复杂度最低的算法，并给出时间复杂度分析。
 */
#include <iostream>
using std::cout; using std::endl;
#include <vector>
using std::vector;

struct topic_info_t {
    int topic_id;
    double topic_pr;
};

//提取递增（无重复）主题ID矢量
static const vector<int> extract_topics(const vector<topic_info_t> &topic_info) {
    vector<int> topic_ids;
    for(auto &r: topic_info)
        topic_ids.push_back(r.topic_id);
    return topic_ids;
}

//从topic_ids主题ID矢量中（从索引为start开始查起）查找主题ID为topic_id的项的索引
static int locate_topic(const vector<int> &topic_ids, int topic_id, const int start) {
    int high = topic_ids.size() - 1, mid, low;
    low = (start > 0)? start: 0;
    while(low <= high) {
        mid = (low+high)/2;
        if (topic_ids[mid] == topic_id)
            return mid;
        else if (topic_ids[mid] < topic_id)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

double max_sim(const vector<topic_info_t>& query_topic_info,
                const vector<topic_info_t> adwords_topic_info[],
                int adwords_number)
{
    double sim_max = 0.0;   //最大相似度值
    
    //提取Query的主题ID矢量
    const vector<int> query_ids = extract_topics(query_topic_info);
    for(int i=0; i < adwords_number; i ++) {    //对每一Adword
        double single_sim = 0.0;    
        int start = 0;  //起始查找位置
        for(auto &ad: adwords_topic_info[i]) {
            int index = locate_topic(query_ids, ad.topic_id, start);
            if(index > 0) {
                single_sim += query_topic_info[index].topic_pr * ad.topic_pr;
                start = index + 1;  //查找成功，则下一次从新的start位置开始查找
            }                       //若查找失败，则下一次还从原来的start位置开始查找
        }
        if (single_sim > sim_max) {
            sim_max = single_sim;
        }
    }
    return sim_max;
}

int main() {
    vector<topic_info_t> query;
    vector<topic_info_t> ad[5];
    for(int i=0; i < 10000; i+= 2) {
        topic_info_t topi = {.topic_id = i, .topic_pr = i/10000.0};
        query.push_back(topi);
    }
    for(int j=0; j < 5; j++) {
        for(int i=0; i < 10000; i += (3+j)) {
            topic_info_t topi = {.topic_id = i, .topic_pr = (j+1)*i/10000.0};
            ad[j].push_back(topi);
        }
    }
    cout << max_sim(query, ad, 5) << endl;
    return 0;
}
